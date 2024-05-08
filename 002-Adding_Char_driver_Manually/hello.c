/*Manually Adding Char device driver*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Second Driver");
MODULE_AUTHOR("HEMA");

int number = 0;
module_param(number, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP);
MODULE_PARM_DESC(number, "major number");

int major_number = 0;
static int driver_open(struct inode *device_file, struct file *instance)
{
    printk("%s dev_nr , open was called\n", __FUNCTION__);
    return 0;
}
static int driver_close(struct inode *device_file, struct file *instance)
{
    printk("%s dev_nr , closed was called\n", __FUNCTION__);
    return 0;
}

struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .open = driver_open,
        .release = driver_close};

static int __init hellodriver_init(void)
{
    int retval;
    major_number = number;
    printk("Hello Driver!\n");

    retval = register_chrdev(major_number, "mytest_driver", &fops);
    if (retval == 0)
    {
        printk("%s retval =0 , Major number = %d , Minor number = %d\n", __FUNCTION__, major_number, 0);
    }
    else
    {
        printk("Couldnot register device number\n");
        return -1;
    }

    return 0;
}
static void __exit hellodriver_exit(void)
{
    unregister_chrdev(major_number, "mytest_driver");
    printk("GoodBye\n");
}

module_init(hellodriver_init);
module_exit(hellodriver_exit);