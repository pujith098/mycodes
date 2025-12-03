// vl805_mmio_rw.c
// Build: make -C /lib/modules/$(uname -r)/build M=$PWD modules
// Tested conceptually for Raspberry Pi 4 (VL805). Use at your own risk.

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/io.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define VL_VENDOR_ID 0x1b73 /* VIA Labs / VLI vendor ID */
#define MODULE_NAME "vl805_mmio_rw"

struct vl805_priv {
    struct pci_dev *pdev;
    void __iomem *mmio;      /* BAR0 mapped base */
    resource_size_t mmio_len;
    unsigned int caplength;
    void __iomem *op_regs;   /* mmio + caplength */
    struct dentry *dbgdir;
};

static struct vl805_priv *global_priv;

/* Read 32-bit helper (safe wrapper) */
static u32 vl805_read32(struct vl805_priv *p, unsigned long offset)
{
    if (!p->mmio) return 0xffffffff;
    if (offset + 4 > p->mmio_len) {
        pr_warn("%s: read32 offset 0x%lx out of range (len 0x%llx)\n",
                MODULE_NAME, offset, (unsigned long long)p->mmio_len);
        return 0xffffffff;
    }
    return readl(p->mmio + offset);
}

/* Write 32-bit helper (dangerous) */
static void vl805_write32(struct vl805_priv *p, unsigned long offset, u32 val)
{
    if (!p->mmio) return;
    if (offset + 4 > p->mmio_len) {
        pr_warn("%s: write32 offset 0x%lx out of range (len 0x%llx)\n",
                MODULE_NAME, offset, (unsigned long long)p->mmio_len);
        return;
    }
    writel(val, p->mmio + offset);
}

/* Populate dmesg with some xHCI operational registers */
static void dump_xhci_basic(struct vl805_priv *p)
{
    u8 caplen;
    u32 usbcmd = 0, usbsts = 0, pagesize = 0, dboff = 0, rtsoff = 0;

    if (!p || !p->mmio) return;
    caplen = readb(p->mmio + 0x00);
    p->caplength = caplen;
    p->op_regs = p->mmio + caplen;

    /* Operational register offsets (from xHCI spec) */
    usbcmd  = readl(p->op_regs + 0x00);
    usbsts  = readl(p->op_regs + 0x04);
    pagesize = readl(p->op_regs + 0x08);
    /* Doorbell offset & runtime register space offset are in capability registers
       Typically DBOFF at cap + 0x14 (32-bit) and RTSOFF at cap + 0x18 (32-bit)
       But some chips place capability parameters differently; reading from CAP regs area below:
    */
    dboff = readl(p->mmio + 0x14);   /* per xHCI spec: DBOFF in cap region */
    rtsoff = readl(p->mmio + 0x18);  /* per xHCI spec: RTSOFF in cap region */

    pr_info("%s: CAPLENGTH=0x%x\n", MODULE_NAME, p->caplength);
    pr_info("%s: op_regs base = %p (mmio %p)\n", MODULE_NAME, p->op_regs, p->mmio);
    pr_info("%s: USBCMD = 0x%08x, USBSTS = 0x%08x, PAGESIZE = 0x%08x\n",
            MODULE_NAME, usbcmd, usbsts, pagesize);
    pr_info("%s: DBOFF = 0x%08x, RTSOFF = 0x%08x\n",
            MODULE_NAME, dboff, rtsoff);
}

/* Simple sysfs-like debugfs command interface:
   Write "R <offset>" to read 32-bit value at offset (hex/dec).
   Write "W <offset> <value>" to write 32-bit value at offset (dangerous).
   Example:      echo "R 0x100" > /sys/kernel/vl805_regs/cmd
                 echo "W 0x100 0x1" > /sys/kernel/vl805_regs/cmd
*/
static ssize_t vl805_dbg_write(struct file *filp, const char __user *buf,
                               size_t count, loff_t *ppos)
{
    char *kbuf;
    unsigned long off = 0;
    unsigned long val = 0;
    int ret;

    if (!global_priv || !global_priv->mmio) return -ENODEV;
    kbuf = kzalloc(min_t(size_t, count, 256), GFP_KERNEL);
    if (!kbuf) return -ENOMEM;
    if (copy_from_user(kbuf, buf, min_t(size_t, count, 255))) {
        kfree(kbuf);
        return -EFAULT;
    }

    /* simple parse */
    if (kbuf[0] == 'R' || kbuf[0] == 'r') {
        ret = kstrtoul(kbuf + 1, 0, &off);
        if (ret) {
            pr_warn("%s: parse error on read\n", MODULE_NAME);
            kfree(kbuf);
            return -EINVAL;
        }
        pr_info("%s: READ offset 0x%lx\n", MODULE_NAME, off);
        pr_info("%s: value = 0x%08x\n", MODULE_NAME, vl805_read32(global_priv, off));
    } else if (kbuf[0] == 'W' || kbuf[0] == 'w') {
        char *p = kbuf + 1;
        ret = kstrtoul(p, 0, &off);
        if (ret) {
            pr_warn("%s: parse error on write(off)\n", MODULE_NAME);
            kfree(kbuf);
            return -EINVAL;
        }
        /* skip token */
        while (*p && !isspace(*p)) p++;
        ret = kstrtoul(p, 0, &val);
        if (ret) {
            pr_warn("%s: parse error on write(val)\n", MODULE_NAME);
            kfree(kbuf);
            return -EINVAL;
        }
        pr_warn("%s: WRITE offset 0x%lx <- 0x%lx (dangerous)\n", MODULE_NAME, off, val);
        vl805_write32(global_priv, off, (u32)val);
    } else {
        pr_warn("%s: unknown command (use 'R offset' or 'W offset value')\n", MODULE_NAME);
        kfree(kbuf);
        return -EINVAL;
    }

    kfree(kbuf);
    return count;
}

static const struct file_operations vl805_dbg_fops = {
    .owner = THIS_MODULE,
    .write = vl805_dbg_write,
};

static int vl805_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
    int err;
    struct vl805_priv *p;
    resource_size_t len;
    void __iomem *mmio;

    pr_info("%s: probe called for vendor 0x%04x, device 0x%04x\n",
            MODULE_NAME, pdev->vendor, pdev->device);

    p = kzalloc(sizeof(*p), GFP_KERNEL);
    if (!p)
        return -ENOMEM;

    p->pdev = pdev;
    pci_set_drvdata(pdev, p);

    err = pci_enable_device(pdev);
    if (err) {
        pr_err("%s: pci_enable_device failed: %d\n", MODULE_NAME, err);
        goto err_free;
    }

    err = pci_request_regions(pdev, MODULE_NAME);
    if (err) {
        pr_err("%s: pci_request_regions failed: %d\n", MODULE_NAME, err);
        goto err_disable;
    }

    /* map BAR0 */
    len = pci_resource_len(pdev, 0);
    mmio = pci_iomap(pdev, 0, 0);
    if (!mmio) {
        pr_err("%s: pci_iomap failed\n", MODULE_NAME);
        err = -ENOMEM;
        goto err_release;
    }

    p->mmio = mmio;
    p->mmio_len = len;
    global_priv = p;

    /* dump basic xHCI info */
    dump_xhci_basic(p);

    /* create debugfs dir and file */
    p->dbgdir = debugfs_create_dir("vl805_regs", NULL);
    if (p->dbgdir) {
        debugfs_create_file("cmd", 0200, p->dbgdir, NULL, &vl805_dbg_fops);
    } else {
        pr_warn("%s: cannot create debugfs dir\n", MODULE_NAME);
    }

    pr_info("%s: probe complete\n", MODULE_NAME);
    return 0;

err_release:
    pci_release_regions(pdev);
err_disable:
    pci_disable_device(pdev);
err_free:
    kfree(p);
    return err;
}

static void vl805_remove(struct pci_dev *pdev)
{
    struct vl805_priv *p = pci_get_drvdata(pdev);

    pr_info("%s: remove called\n", MODULE_NAME);
    if (!p) return;

    if (p->dbgdir)
        debugfs_remove_recursive(p->dbgdir);

    if (p->mmio)
        pci_iounmap(pdev, p->mmio);

    pci_release_regions(pdev);
    pci_disable_device(pdev);

    kfree(p);
    global_priv = NULL;
}

/* Match any device from VL vendor (PCI_ANY_ID for device ID) */
static const struct pci_device_id vl805_ids[] = {
    { PCI_ANY_ID, VL_VENDOR_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
    { 0, }
};
MODULE_DEVICE_TABLE(pci, vl805_ids);

static struct pci_driver vl805_pci_driver = {
    .name = MODULE_NAME,
    .id_table = vl805_ids,
    .probe = vl805_probe,
    .remove = vl805_remove,
};

module_pci_driver(vl805_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("pujit");
MODULE_DESCRIPTION("VL805 PCIe MMIO reader/writer (experimental) - Raspberry Pi 4");

