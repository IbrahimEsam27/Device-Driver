#include <linux/module.h>
#include <linux/init.h>

int mydriver_init (void)
{
    printk("Init Driver Function\n");
    return 0;
}

void mydriver_exit (void)
{
        printk("Bye Bye\n");
}

module_init(mydriver_init);
module_exit(mydriver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Everything");
MODULE_AUTHOR("HEMA");