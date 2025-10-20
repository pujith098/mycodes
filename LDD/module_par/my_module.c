#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static int myint = 10;

// module_param style (simple)
module_param(myint, int, 0644);
MODULE_PARM_DESC(myint, "A simple integer module parameter");


// module_param_cb style (custom set/get)
static int customval = 20;

static int my_set(const char *val, const struct kernel_param *kp)
{
    int ret = param_set_int(val, kp);  // Default setter
    if (ret == 0)
        printk(KERN_INFO "customval updated to %d\n", customval);
    return ret;
}

static int my_get(char *buffer, const struct kernel_param *kp)
{
    printk(KERN_INFO "customval read: %d\n", customval);
    return param_get_int(buffer, kp);  // Default getter
}

static const struct kernel_param_ops my_ops = {
    .set = my_set,
    .get = my_get,
};

module_param_cb(customval, &my_ops, &customval, 0644);
MODULE_PARM_DESC(customval, "Custom handled int parameter");

static int __init my_module_init(void)
{
    printk(KERN_INFO "Module loaded: myint = %d, customval = %d\n", myint, customval);
    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Module exiting.\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("pujit");
MODULE_DESCRIPTION("Module param and param_cb test");

