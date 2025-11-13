/*
 * custom_usb_mass.c
 *
 * Corrected safer USB Mass Storage test driver (minimal)
 * - Proper CBW/CSW structures with endian handling
 * - DMA-safe allocations for transfers (usb_alloc_coherent / kmalloc)
 * - GET_MAX_LUN handling
 * - Bulk-Only Mass Storage Reset + clear_halt recovery
 * - Deferred INQUIRY via workqueue (no long blocking in probe)
 * - Extra debug prints
 *
 * NOTE: This is still a **toy/test** driver — it does not implement
 * SCSI mid-layer integration or full performance logic found in
 * drivers/usb/storage/usb.c. It's a much safer stepping stone toward that.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/slab.h>
#include <linux/usb/ch9.h>
#include <linux/byteorder/generic.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

#define VENDOR_ID   0x03F0  /* HP Vendor ID */
#define PRODUCT_ID  0x2003  /* HP Flash Drive Product ID */

#define USB_BULK_CB_WRAP_LEN 31
#define USB_BULK_CS_WRAP_LEN 13

/* Class-specific requests for Bulk-Only Transport (BOT) */
#define USB_BULK_REQ_GET_MAX_LUN 0xFE
#define USB_BULK_REQ_RESET        0xFF

/* Timeout values (ms) */
#define CBW_SEND_TIMEOUT_MS   1000
#define DATA_RECV_TIMEOUT_MS  2000
#define CSW_RECV_TIMEOUT_MS   1000

/* Table of supported devices */
static const struct usb_device_id usb_table[] = {
    { USB_DEVICE(VENDOR_ID, PRODUCT_ID) },
    { } /* terminating entry */
};
MODULE_DEVICE_TABLE(usb, usb_table);

/* Packed CBW (Command Block Wrapper) */
struct bulk_cb_wrap {
    __le32  Signature;            /* 'USBC' => 0x43425355 */
    __le32  Tag;
    __le32  DataTransferLength;
    u8      Flags;
    u8      LUN;
    u8      CBLength;
    u8      CDB[16];
} __attribute__((packed));

/* Device private structure */
struct usb_mass_dev {
    struct usb_device *udev;
    struct usb_interface *interface;

    unsigned char bulk_in_ep;
    unsigned char bulk_out_ep;
    unsigned int  bulk_in_size;
    unsigned int  bulk_out_size;

    struct work_struct inquiry_work;
    int max_lun;
    u32 cbw_tag;
};

static void usb_mass_do_reset(struct usb_mass_dev *dev)
{
    int ret;

    pr_info("[USB] mass_reset: issuing Bulk-Only Mass Storage Reset\n");

    /* Class-specific request: Mass Storage Reset (Host->Device) */
    ret = usb_control_msg(dev->udev,
                          usb_sndctrlpipe(dev->udev, 0),
                          USB_BULK_REQ_RESET,
                          USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                          0, /* wValue */
                          dev->interface->cur_altsetting->desc.bInterfaceNumber,
                          NULL, 0,
                          1000);
    if (ret < 0)
        pr_err("[USB] mass_reset control_msg failed: %d\n", ret);
    else
        pr_info("[USB] mass_reset control_msg OK\n");

    /* clear halt on both endpoints (IN and OUT) to recover from stall */
    if (dev->bulk_in_ep) {
        pr_info("[USB] clearing halt on bulk_in 0x%02x\n", dev->bulk_in_ep);
        usb_clear_halt(dev->udev, usb_rcvbulkpipe(dev->udev, dev->bulk_in_ep));
    }
    if (dev->bulk_out_ep) {
        pr_info("[USB] clearing halt on bulk_out 0x%02x\n", dev->bulk_out_ep);
        usb_clear_halt(dev->udev, usb_sndbulkpipe(dev->udev, dev->bulk_out_ep));
    }

    /* small delay to give device time after reset */
    msleep(100);
}

/* Helper: perform GET_MAX_LUN; returns >=0 for max_lun, or -errno */
static int usb_mass_get_max_lun(struct usb_mass_dev *dev)
{
    int ret;
    u8 *buf;

    buf = kmalloc(1, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    /* GET_MAX_LUN is device->host class request */
    ret = usb_control_msg(dev->udev,
                          usb_rcvctrlpipe(dev->udev, 0),
                          USB_BULK_REQ_GET_MAX_LUN,
                          USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                          0,
                          dev->interface->cur_altsetting->desc.bInterfaceNumber,
                          buf, 1,
                          1000);

    if (ret < 0) {
        pr_warn("[USB] GET_MAX_LUN failed (may be unsupported): %d\n", ret);
        kfree(buf);
        /* Many devices stall/return error - default to LUN 0 */
        return -EIO;
    }

    pr_info("[USB] GET_MAX_LUN returned %u\n", buf[0]);
    ret = buf[0];
    kfree(buf);
    return ret;
}

/* Minimal safe send_inquiry using DMA-safe buffers (usb_alloc_coherent)
 * Synchronous for simplicity (usb_bulk_msg). Returns 0 on success or negative error.
 */
static int send_inquiry_sync(struct usb_mass_dev *dev)
{
    int retval = 0;
    struct bulk_cb_wrap *cbw = NULL;
    void *cbw_dma = NULL;
    void *data_buf = NULL;
    dma_addr_t data_dma = 0;
    void *csw_buf = NULL;
    int actual_length;

    pr_info("[USB] send_inquiry_sync: preparing INQUIRY (tag=%u)\n", dev->cbw_tag);

    /* Allocate coherent DMA-safe buffers for CBW, data and CSW.
     * Note: usb_alloc_coherent returns DMA-coherent memory and the DMA address.
     */
    cbw = usb_alloc_coherent(dev->udev, sizeof(*cbw), GFP_KERNEL, &data_dma /* re-use var */);
    if (!cbw) {
        pr_err("[USB] Failed to usb_alloc_coherent CBW\n");
        retval = -ENOMEM;
        goto out;
    }
    cbw_dma = cbw; /* logical pointer for clarity */

    data_buf = usb_alloc_coherent(dev->udev, 36, GFP_KERNEL, &data_dma);
    if (!data_buf) {
        pr_err("[USB] Failed to usb_alloc_coherent data_buf\n");
        retval = -ENOMEM;
        goto free_cbw;
    }

    csw_buf = usb_alloc_coherent(dev->udev, USB_BULK_CS_WRAP_LEN, GFP_KERNEL, &data_dma);
    if (!csw_buf) {
        pr_err("[USB] Failed to usb_alloc_coherent csw_buf\n");
        retval = -ENOMEM;
        goto free_data;
    }

    /* Clear buffers */
    memset(cbw, 0, sizeof(*cbw));
    memset(data_buf, 0, 36);
    memset(csw_buf, 0, USB_BULK_CS_WRAP_LEN);

    /* Fill CBW properly (little endian fields) */
    cbw->Signature = cpu_to_le32(0x43425355); /* 'USBC' */
    cbw->Tag = cpu_to_le32(dev->cbw_tag);
    cbw->DataTransferLength = cpu_to_le32(36);
    cbw->Flags = 0x80; /* IN transfer (device -> host) */
    cbw->LUN = 0;
    cbw->CBLength = 6;
    cbw->CDB[0] = 0x12; /* INQUIRY */
    cbw->CDB[4] = 36;   /* allocation length */

    pr_info("[USB] Sending CBW (size=%zu) to bulk-out 0x%02x\n",
            sizeof(*cbw),
            dev->bulk_out_ep);

    retval = usb_bulk_msg(dev->udev,
                          usb_sndbulkpipe(dev->udev, dev->bulk_out_ep),
                          cbw, sizeof(*cbw), &actual_length,
                          CBW_SEND_TIMEOUT_MS);
    if (retval) {
        pr_err("[USB] usb_bulk_msg(CBW) failed: %d\n", retval);
        /* attempt reset recovery */
        usb_mass_do_reset(dev);
        goto free_csw;
    }
    pr_info("[USB] CBW sent (%d bytes)\n", actual_length);

    /* Read INQUIRY data (device -> host) */
    retval = usb_bulk_msg(dev->udev,
                          usb_rcvbulkpipe(dev->udev, dev->bulk_in_ep),
                          data_buf, 36, &actual_length,
                          DATA_RECV_TIMEOUT_MS);
    if (retval) {
        pr_err("[USB] usb_bulk_msg(INQUIRY data) failed: %d\n", retval);
        usb_mass_do_reset(dev);
        goto free_csw;
    }

    pr_info("[USB] INQUIRY Data Received (%d bytes)\n", actual_length);
    print_hex_dump(KERN_INFO, "[INQUIRY] ", DUMP_PREFIX_OFFSET, 16, 1,
                   data_buf, actual_length, true);

    /* Read CSW */
    retval = usb_bulk_msg(dev->udev,
                          usb_rcvbulkpipe(dev->udev, dev->bulk_in_ep),
                          csw_buf, USB_BULK_CS_WRAP_LEN, &actual_length,
                          CSW_RECV_TIMEOUT_MS);
    if (retval) {
        pr_err("[USB] usb_bulk_msg(CSW) failed: %d\n", retval);
        usb_mass_do_reset(dev);
        goto free_csw;
    }

    pr_info("[USB] CSW received (%d bytes)\n", actual_length);
    print_hex_dump(KERN_INFO, "[CSW] ", DUMP_PREFIX_OFFSET, 16, 1,
                   csw_buf, actual_length, true);

    /* Basic CSW checks (signature & status) */
    if (actual_length >= 13) {
        __le32 sig = *(__le32 *)((u8 *)csw_buf + 0);
        if (le32_to_cpu(sig) != 0x53425355) { /* 'USBS' */
            pr_err("[USB] Invalid CSW signature: 0x%08x\n", le32_to_cpu(sig));
            retval = -EIO;
        } else {
            u8 status = *((u8 *)csw_buf + 12);
            pr_info("[USB] CSW status: 0x%02x\n", status);
            if (status != 0)
                pr_warn("[USB] CSW reports command failed (status=%u)\n", status);
        }
    } else {
        pr_warn("[USB] CSW too short (%d bytes)\n", actual_length);
        retval = -EIO;
    }

free_csw:
    usb_free_coherent(dev->udev, USB_BULK_CS_WRAP_LEN, csw_buf, 0);
free_data:
    usb_free_coherent(dev->udev, 36, data_buf, 0);
free_cbw:
    usb_free_coherent(dev->udev, sizeof(*cbw), cbw, 0);
out:
    return retval;
}

/* Workqueue handler for running GET_MAX_LUN + INQUIRY (deferred from probe) */
static void inquiry_work_func(struct work_struct *work)
{
    struct usb_mass_dev *dev = container_of(work, struct usb_mass_dev, inquiry_work);
    int ret;

    pr_info("[USB WORK] inquiry_work_func started for device %04x:%04x\n",
            dev->udev->descriptor.idVendor, dev->udev->descriptor.idProduct);

    /* attempt GET_MAX_LUN */
    ret = usb_mass_get_max_lun(dev);
    if (ret >= 0) {
        dev->max_lun = ret;
        pr_info("[USB WORK] Device supports max LUN = %d\n", dev->max_lun);
    } else {
        pr_info("[USB WORK] GET_MAX_LUN not supported or failed -> assuming max_lun = 0\n");
        dev->max_lun = 0;
    }

    /* increment tag */
    dev->cbw_tag++;

    /* perform single INQUIRY for testing */
    ret = send_inquiry_sync(dev);
    if (ret)
        pr_err("[USB WORK] send_inquiry_sync failed: %d\n", ret);
    else
        pr_info("[USB WORK] send_inquiry_sync completed successfully\n");

    pr_info("[USB WORK] inquiry_work_func finished\n");
}

/* ========================== PROBE ========================== */
static int usb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct usb_mass_dev *dev;
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    pr_info("[USB] ===== USB PROBE =====\n");
    pr_info("[USB] Device plugged in: Vendor=0x%04x, Product=0x%04x\n",
            id->idVendor, id->idProduct);

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->udev = usb_get_dev(interface_to_usbdev(interface));
    dev->interface = interface;
    dev->cbw_tag = 1;

    iface_desc = interface->cur_altsetting;

    pr_info("[USB] Interface number: %d\n", iface_desc->desc.bInterfaceNumber);
    pr_info("[USB] Number of endpoints: %d\n", iface_desc->desc.bNumEndpoints);

    /* iterate endpoints and find bulk in/out */
    for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
        endpoint = &iface_desc->endpoint[i].desc;
        pr_info("[USB] Checking endpoint %d:\n", i);
        pr_info("  Endpoint Address: 0x%02x\n", endpoint->bEndpointAddress);
        pr_info("  Attributes: 0x%02x (%s)\n",
                endpoint->bmAttributes,
                (endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK ? "Bulk" : "Other");
        pr_info("  Max Packet Size: %u\n", le16_to_cpu(endpoint->wMaxPacketSize));
        pr_info("  Interval: %u\n", endpoint->bInterval);

        if (usb_endpoint_is_bulk_in(endpoint)) {
            dev->bulk_in_ep = endpoint->bEndpointAddress;
            dev->bulk_in_size = usb_endpoint_maxp(endpoint);
            pr_info("[USB] -> Bulk IN endpoint found: 0x%02x (Size: %u)\n",
                    dev->bulk_in_ep, dev->bulk_in_size);
        } else if (usb_endpoint_is_bulk_out(endpoint)) {
            dev->bulk_out_ep = endpoint->bEndpointAddress;
            dev->bulk_out_size = usb_endpoint_maxp(endpoint);
            pr_info("[USB] -> Bulk OUT endpoint found: 0x%02x (Size: %u)\n",
                    dev->bulk_out_ep, dev->bulk_out_size);
        }
    }

    if (!dev->bulk_in_ep || !dev->bulk_out_ep) {
        pr_err("[USB] Bulk IN/OUT endpoints not found! Exiting probe...\n");
        usb_put_dev(dev->udev);
        kfree(dev);
        return -ENODEV;
    }

    /* set interface-specific data */
    usb_set_intfdata(interface, dev);

    /* initialize and queue deferred work to run INQUIRY (avoid long waits in probe) */
    INIT_WORK(&dev->inquiry_work, inquiry_work_func);

    /* schedule the work (runs in system workqueue) */
    schedule_work(&dev->inquiry_work);

    pr_info("[USB] Driver successfully bound to device (deferred inquiry scheduled).\n");
    return 0;
}

/* ========================== DISCONNECT ========================== */
static void usb_disconnect(struct usb_interface *interface)
{
    struct usb_mass_dev *dev = usb_get_intfdata(interface);

    pr_info("[USB] ===== USB DISCONNECT =====\n");

    usb_set_intfdata(interface, NULL);

    if (!dev) {
        pr_warn("[USB] usb_disconnect: no dev data found\n");
        return;
    }

    /* cancel pending work */
    if (cancel_work_sync(&dev->inquiry_work))
        pr_info("[USB] Pending inquiry work cancelled\n");

    usb_put_dev(dev->udev);
    kfree(dev);

    pr_info("[USB] Custom USB Mass Storage driver disconnected.\n");
}

/* ========================== DRIVER STRUCT ========================== */
static struct usb_driver usb_mass_driver = {
    .name       = "custom_usb_mass",
    .id_table   = usb_table,
    .probe      = usb_probe,
    .disconnect = usb_disconnect,
};

module_usb_driver(usb_mass_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pujith (corrected)");
MODULE_DESCRIPTION("Custom USB Mass Storage Driver (corrected, DMA-safe, deferred INQUIRY, debug)");

