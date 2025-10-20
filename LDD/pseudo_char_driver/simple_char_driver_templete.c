// pseudo_char_complete.c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/types.h>

#define DEVICE_NAME     "pseudo_char_dev"
#define CLASS_NAME      "pseudo_class"
#define NUM_DEVICES     4
#define BUFFER_SIZE     1024
#define MAGIC_NUM       0xF0

/* IOCTLs */
#define CLEAR_BUFFER    _IO(MAGIC_NUM, 0)
#define GET_BUF_SIZE    _IOR(MAGIC_NUM, 1, size_t)
struct pseudo_stats {
    u64 bytes_read;
    u64 bytes_written;
    u32 times_cleared;
};
#define GET_STATS       _IOR(MAGIC_NUM, 2, struct pseudo_stats)

struct pseudo_device {
    char *buffer;                 /* device buffer */
    size_t buf_size;              /* capacity (BUFFER_SIZE) */
    struct cdev cdev;
    struct device *dev;           /* device returned by device_create */
    struct mutex lock;            /* protect buffer and stats */
    wait_queue_head_t rq;         /* readers wait on data availability */
    u64 bytes_read;
    u64 bytes_written;
    u32 times_cleared;
};

static dev_t dev_num_base;
static struct class *pseudo_class;
static struct pseudo_device *pseudo_devices;

/* ---------- file operations ---------- */

static int pseudo_open(struct inode *inode, struct file *file)
{
    struct pseudo_device *pdev = container_of(inode->i_cdev, struct pseudo_device, cdev);
    file->private_data = pdev;
    pr_info("[PseudoChar] Device opened\n");
    return 0;
}

static int pseudo_release(struct inode *inode, struct file *file)
{
    pr_info("[PseudoChar] Device closed\n");
    return 0;
}

/* llseek: set file position relative to start/cur/end */
static loff_t pseudo_llseek(struct file *file, loff_t offset, int whence)
{
    struct pseudo_device *pdev = file->private_data;
    loff_t new_pos;

    if (!pdev)
        return -EINVAL;

    switch (whence) {
    case SEEK_SET:
        new_pos = offset;
        break;
    case SEEK_CUR:
        new_pos = file->f_pos + offset;
        break;
    case SEEK_END:
        new_pos = pdev->buf_size + offset;
        break;
    default:
        return -EINVAL;
    }

    if (new_pos < 0 || new_pos > (loff_t)pdev->buf_size)
        return -EINVAL;

    file->f_pos = new_pos;
    return new_pos;
}

/* read: copy from device buffer starting at file->f_pos */
static ssize_t pseudo_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    struct pseudo_device *pdev = file->private_data;
    ssize_t to_copy;

    if (!pdev)
        return -EFAULT;

    if (mutex_lock_interruptible(&pdev->lock))
        return -EINTR;

    if (*offset >= pdev->buf_size) {
        mutex_unlock(&pdev->lock);
        return 0;
    }

    if ((*offset + len) > pdev->buf_size)
        to_copy = pdev->buf_size - *offset;
    else
        to_copy = len;

    if (copy_to_user(buf, pdev->buffer + *offset, to_copy)) {
        mutex_unlock(&pdev->lock);
        return -EFAULT;
    }

    *offset += to_copy;
    pdev->bytes_read += to_copy;
    mutex_unlock(&pdev->lock);

    pr_debug("[PseudoChar] Read %zd bytes, new offset %lld\n", to_copy, (long long)*offset);
    return to_copy;
}

/* write: copy into device buffer starting at file->f_pos */
static ssize_t pseudo_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    struct pseudo_device *pdev = file->private_data;
    ssize_t to_copy;

    if (!pdev)
        return -EFAULT;

    if (mutex_lock_interruptible(&pdev->lock))
        return -EINTR;

    if (*offset >= pdev->buf_size) {
        mutex_unlock(&pdev->lock);
        return -ENOSPC;
    }

    if ((*offset + len) > pdev->buf_size)
        to_copy = pdev->buf_size - *offset;
    else
        to_copy = len;

    if (copy_from_user(pdev->buffer + *offset, buf, to_copy)) {
        mutex_unlock(&pdev->lock);
        return -EFAULT;
    }

    *offset += to_copy;
    pdev->bytes_written += to_copy;

    /* wake readers waiting for data */
    wake_up_interruptible(&pdev->rq);

    mutex_unlock(&pdev->lock);

    pr_debug("[PseudoChar] Written %zd bytes, new offset %lld\n", to_copy, (long long)*offset);
    return to_copy;
}

/* poll: report readability/writability */
static unsigned int pseudo_poll(struct file *file, poll_table *wait)
{
    struct pseudo_device *pdev = file->private_data;
    unsigned int mask = 0;

    if (!pdev)
        return POLLERR;

    /* wait for readers on the device's wait queue */
    poll_wait(file, &pdev->rq, wait);

    /* Data is considered "available" if there exists any non-zero byte in buffer.
       A simpler approach: treat any position less than buf_size as available. */
    mutex_lock(&pdev->lock);
    if (file->f_pos < pdev->buf_size)
        mask |= POLLIN | POLLRDNORM; /* readable */
    /* writable if there is free space after f_pos */
    if (file->f_pos < pdev->buf_size)
        mask |= POLLOUT | POLLWRNORM;
    mutex_unlock(&pdev->lock);

    return mask;
}

/* ioctl: CLEAR_BUFFER, GET_BUF_SIZE, GET_STATS */
static long pseudo_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    struct pseudo_device *pdev = file->private_data;
    struct pseudo_stats stats;
    size_t size;

    if (!pdev)
        return -EFAULT;

    switch (cmd) {
    case CLEAR_BUFFER:
        mutex_lock(&pdev->lock);
        memset(pdev->buffer, 0, pdev->buf_size);
        pdev->times_cleared++;
        /* wake readers (they may see EOF/zeroes) */
        wake_up_interruptible(&pdev->rq);
        mutex_unlock(&pdev->lock);
        pr_info("[PseudoChar] Buffer cleared via ioctl\n");
        break;

    case GET_BUF_SIZE:
        size = pdev->buf_size;
        if (copy_to_user((size_t __user *)arg, &size, sizeof(size_t)))
            return -EFAULT;
        break;

    case GET_STATS:
        mutex_lock(&pdev->lock);
        stats.bytes_read = pdev->bytes_read;
        stats.bytes_written = pdev->bytes_written;
        stats.times_cleared = pdev->times_cleared;
        mutex_unlock(&pdev->lock);
        if (copy_to_user((struct pseudo_stats __user *)arg, &stats, sizeof(stats)))
            return -EFAULT;
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

/* File operations structure */
static const struct file_operations pseudo_fops = {
    .owner = THIS_MODULE,
    .open = pseudo_open,
    .release = pseudo_release,
    .read = pseudo_read,
    .write = pseudo_write,
    .llseek = pseudo_llseek,
    .poll = pseudo_poll,
    .unlocked_ioctl = pseudo_ioctl,
};

/* ---------- sysfs attributes (per-device) ---------- */

static ssize_t bufsize_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct pseudo_device *pdev = dev_get_drvdata(dev);
    return sprintf(buf, "%zu\n", pdev->buf_size);
}
static DEVICE_ATTR_RO(bufsize);

static ssize_t data_used_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct pseudo_device *pdev = dev_get_drvdata(dev);
    /* data used is approximate; we consider maximum index touched = buf_size if non-zero */
    /* For simplicity return total bytes_written */
    return sprintf(buf, "%llu\n", (unsigned long long)pdev->bytes_written);
}
static DEVICE_ATTR_RO(data_used);

/* ---------- module init / exit ---------- */

static int __init pseudo_init(void)
{
    int ret = 0;
    int i;

    ret = alloc_chrdev_region(&dev_num_base, 0, NUM_DEVICES, DEVICE_NAME);
    if (ret < 0) {
        pr_alert("[PseudoChar] Failed to allocate device numbers\n");
        return ret;
    }

    pseudo_devices = kzalloc(sizeof(*pseudo_devices) * NUM_DEVICES, GFP_KERNEL);
    if (!pseudo_devices) {
        unregister_chrdev_region(dev_num_base, NUM_DEVICES);
        return -ENOMEM;
    }

    pseudo_class = class_create(CLASS_NAME);
    if (IS_ERR(pseudo_class)) {
        ret = PTR_ERR(pseudo_class);
        pr_alert("[PseudoChar] class_create failed\n");
        goto err_free_array;
    }

    for (i = 0; i < NUM_DEVICES; i++) {
        struct pseudo_device *pdev = &pseudo_devices[i];
        pdev->buf_size = BUFFER_SIZE;
        pdev->buffer = kzalloc(pdev->buf_size, GFP_KERNEL);
        if (!pdev->buffer) {
            ret = -ENOMEM;
            pr_alert("[PseudoChar] buffer alloc failed for device %d\n", i);
            goto err_cleanup_devices;
        }

        mutex_init(&pdev->lock);
        init_waitqueue_head(&pdev->rq);

        cdev_init(&pdev->cdev, &pseudo_fops);
        pdev->cdev.owner = THIS_MODULE;

        ret = cdev_add(&pdev->cdev, dev_num_base + i, 1);
        if (ret) {
            pr_alert("[PseudoChar] cdev_add failed for %d\n", i);
            kfree(pdev->buffer);
            goto err_cleanup_devices;
        }

        /* create device node and store returned device */
        pdev->dev = device_create(pseudo_class, NULL, dev_num_base + i, NULL, DEVICE_NAME "%d", i);
        if (IS_ERR(pdev->dev)) {
            pr_alert("[PseudoChar] device_create failed for %d\n", i);
            ret = PTR_ERR(pdev->dev);
            cdev_del(&pdev->cdev);
            kfree(pdev->buffer);
            goto err_cleanup_devices;
        }

        /* attach driver data for sysfs callbacks */
        dev_set_drvdata(pdev->dev, pdev);

        /* create sysfs attributes for this device */
        ret = device_create_file(pdev->dev, &dev_attr_bufsize);
        if (ret) {
            pr_warn("[PseudoChar] device_create_file bufsize failed for %d\n", i);
            /* non-fatal: continue */
        }
        ret = device_create_file(pdev->dev, &dev_attr_data_used);
        if (ret) {
            pr_warn("[PseudoChar] device_create_file data_used failed for %d\n", i);
        }
        /* reset ret for next iteration */
        ret = 0;
    }

    pr_info("[PseudoChar] Loaded %d devices (major %d)\n", NUM_DEVICES, MAJOR(dev_num_base));
    return 0;

err_cleanup_devices:
    /* rollback created devices so far */
    while (--i >= 0) {
        struct pseudo_device *pdev = &pseudo_devices[i];
        if (pdev->dev) {
            device_remove_file(pdev->dev, &dev_attr_data_used);
            device_remove_file(pdev->dev, &dev_attr_bufsize);
            device_destroy(pseudo_class, dev_num_base + i);
        }
        cdev_del(&pdev->cdev);
        kfree(pdev->buffer);
    }
    class_destroy(pseudo_class);
err_free_array:
    kfree(pseudo_devices);
    unregister_chrdev_region(dev_num_base, NUM_DEVICES);
    return ret;
}

static void __exit pseudo_exit(void)
{
    int i;
    for (i = 0; i < NUM_DEVICES; i++) {
        struct pseudo_device *pdev = &pseudo_devices[i];
        if (!pdev)
            continue;
        if (pdev->dev) {
            device_remove_file(pdev->dev, &dev_attr_data_used);
            device_remove_file(pdev->dev, &dev_attr_bufsize);
            device_destroy(pseudo_class, dev_num_base + i);
        }
        cdev_del(&pdev->cdev);
        kfree(pdev->buffer);
    }
    class_destroy(pseudo_class);
    kfree(pseudo_devices);
    unregister_chrdev_region(dev_num_base, NUM_DEVICES);
    pr_info("[PseudoChar] Unloaded %d devices\n", NUM_DEVICES);
}

module_init(pseudo_init);
module_exit(pseudo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHEELI Pujitkumar");
MODULE_DESCRIPTION("Complete Multi-Device Pseudo Char Driver (with mutex, poll, llseek, sysfs)");
MODULE_VERSION("4.0");
