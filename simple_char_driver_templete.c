#include <linux/module.h>          // Core header for loading LKMs into the kernel
#include <linux/init.h>            // Macros used to mark up functions e.g., __init __exit
#include <linux/fs.h>              // File operations structure
#include <linux/cdev.h>            // Character device registration
#include <linux/device.h>          // Device creation in /dev via udev
#include <linux/slab.h>            // kmalloc and kfree
#include <linux/uaccess.h>         // copy_to_user and copy_from_user
#include <linux/ioctl.h>           // ioctl definitions

#define DEVICE_NAME     "pseudo_char_dev"    // Base name for device nodes
#define CLASS_NAME      "pseudo_class"       // Class name for sysfs
#define NUM_DEVICES     4                    // Number of devices to create
#define BUFFER_SIZE     1024                 // Size of each device buffer
#define MAGIC_NUM       0xF0                 // Magic number for ioctl
#define CLEAR_BUFFER    _IO(MAGIC_NUM, 0)    // ioctl command to clear buffer

// Per-device structure
struct pseudo_device {
    char *buffer;              // Device buffer (simulated memory)
    struct cdev cdev;          // Character device structure
};

static struct pseudo_device *pseudo_devices; // Array of devices
static dev_t dev_num_base;                   // Starting dev_t (major/minor)
static struct class *pseudo_class;           // Device class pointer

// ---------------- File Operations ----------------

static int pseudo_open(struct inode *inode, struct file *file) {
    // Get the pseudo_device using container_of
    struct pseudo_device *pdev = container_of(inode->i_cdev, struct pseudo_device, cdev);
    file->private_data = pdev; // Save device pointer for use in read/write/ioctl
    printk(KERN_INFO "[PseudoChar] Device opened\n");
    return 0;
}

static int pseudo_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "[PseudoChar] Device closed\n");
    return 0;
}

static ssize_t pseudo_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    struct pseudo_device *pdev = file->private_data;

    if (*offset >= BUFFER_SIZE)
        return 0;

    if ((*offset + len) > BUFFER_SIZE)
        len = BUFFER_SIZE - *offset;

    if (copy_to_user(buf, pdev->buffer + *offset, len))
        return -EFAULT;

    *offset += len;
    printk(KERN_INFO "[PseudoChar] Read %zu bytes\n", len);
    return len;
}

static ssize_t pseudo_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    struct pseudo_device *pdev = file->private_data;

    if (*offset >= BUFFER_SIZE)
        return -ENOSPC;

    if ((*offset + len) > BUFFER_SIZE)
        len = BUFFER_SIZE - *offset;

    if (copy_from_user(pdev->buffer + *offset, buf, len))
        return -EFAULT;

    *offset += len;
    printk(KERN_INFO "[PseudoChar] Written %zu bytes\n", len);
    return len;
}

static long pseudo_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct pseudo_device *pdev = file->private_data;

    switch (cmd) {
        case CLEAR_BUFFER:
            memset(pdev->buffer, 0, BUFFER_SIZE); // Clear the device buffer
            printk(KERN_INFO "[PseudoChar] Buffer cleared via ioctl\n");
            break;
        default:
            return -EINVAL;
    }

    return 0;
}

// File operations structure (shared by all devices)
static struct file_operations pseudo_fops = {
    .owner = THIS_MODULE,
    .open = pseudo_open,
    .release = pseudo_release,
    .read = pseudo_read,
    .write = pseudo_write,
    .unlocked_ioctl = pseudo_ioctl,
};

// ---------------- Module Init ----------------

static int __init pseudo_init(void) {
    int ret, i;

    // Allocate a range of device numbers (one for each device)
    ret = alloc_chrdev_region(&dev_num_base, 0, NUM_DEVICES, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "[PseudoChar] Failed to allocate device numbers\n");
        return ret;
    }

    // Allocate memory for all pseudo devices
    pseudo_devices = kzalloc(sizeof(struct pseudo_device) * NUM_DEVICES, GFP_KERNEL);
    if (!pseudo_devices) {
        unregister_chrdev_region(dev_num_base, NUM_DEVICES);
        return -ENOMEM;
    }

    // Create device class for udev to auto-create /dev entries
    pseudo_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(pseudo_class)) {
        kfree(pseudo_devices);
        unregister_chrdev_region(dev_num_base, NUM_DEVICES);
        return PTR_ERR(pseudo_class);
    }

    // Initialize each device
    for (i = 0; i < NUM_DEVICES; i++) {
        // Allocate memory for each device buffer
        pseudo_devices[i].buffer = kzalloc(BUFFER_SIZE, GFP_KERNEL);
        if (!pseudo_devices[i].buffer) {
            while (--i >= 0)
                kfree(pseudo_devices[i].buffer);
            class_destroy(pseudo_class);
            kfree(pseudo_devices);
            unregister_chrdev_region(dev_num_base, NUM_DEVICES);
            return -ENOMEM;
        }

        // Initialize cdev and add to kernel
        cdev_init(&pseudo_devices[i].cdev, &pseudo_fops);
        pseudo_devices[i].cdev.owner = THIS_MODULE;

        ret = cdev_add(&pseudo_devices[i].cdev, dev_num_base + i, 1);
        if (ret < 0) {
            printk(KERN_ALERT "[PseudoChar] Failed to add cdev %d\n", i);
            while (--i >= 0) {
                cdev_del(&pseudo_devices[i].cdev);
                kfree(pseudo_devices[i].buffer);
            }
            class_destroy(pseudo_class);
            kfree(pseudo_devices);
            unregister_chrdev_region(dev_num_base, NUM_DEVICES);
            return ret;
        }

        // Create device entry in /dev/
        device_create(pseudo_class, NULL, dev_num_base + i, NULL, DEVICE_NAME "%d", i);
    }

    printk(KERN_INFO "[PseudoChar] Loaded %d devices with major %d\n", NUM_DEVICES, MAJOR(dev_num_base));
    return 0;
}

// ---------------- Module Exit ----------------

static void __exit pseudo_exit(void) {
    int i;

    // Remove devices and cleanup
    for (i = 0; i < NUM_DEVICES; i++) {
        device_destroy(pseudo_class, dev_num_base + i);        // Remove /dev/pseudo_char_devX
        cdev_del(&pseudo_devices[i].cdev);                     // Remove cdev from kernel
        kfree(pseudo_devices[i].buffer);                       // Free buffer
    }

    class_destroy(pseudo_class);           // Remove sysfs class
    kfree(pseudo_devices);                 // Free device array
    unregister_chrdev_region(dev_num_base, NUM_DEVICES);  // Release device numbers

    printk(KERN_INFO "[PseudoChar] Unloaded %d devices\n", NUM_DEVICES);
}

module_init(pseudo_init);
module_exit(pseudo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHEELI Pujitkumar");
MODULE_DESCRIPTION("Modern Multi-Device Pseudo Char Driver");
MODULE_VERSION("3.0");
