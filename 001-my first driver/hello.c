#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Second Driver");
MODULE_AUTHOR("HEMA");

static int __init hellodriver_init(void)
{
    printk("Hello, world\n");
    return 0;
}
static void __exit hellodriver_exit(void)
{
	printk("Goodbye, world\n");

}

module_init(hellodriver_init);

module_exit(hellodriver_exit);