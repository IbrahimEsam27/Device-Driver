# Simple Driver
## steps
### 1. write ``main.c`` (_which will be written in the kernel space_)

> Things written in kernel space don't see glibc library ---> so kernel provides equivelent functions in kernel space.
>
> ***ex:*** ``printf`` in glibc == ``printk`` in kernel space

**main.c**
```c
#include <linux/module.h>
#include <linux/init.h>

//Meta information
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
```
**``module_init``** serves as the entry point for kernel modules, initializing resources and registering device drivers upon module loading. Unlike in GCC where the startup code searches for the main function, in kernel builds, it looks for module_init as the entry point, executing the specified function at the start of the program.

**``module_exit``** serves as the exit point for kernel modules, releasing resources and unregistering device drivers before unloading the module. Similar to module_init, it defines a function that is executed at the end of the program's execution.

**``static int __init``** to put the function **``hellodriver_init``** ---> **.init** section in memory , after executing that function it will be removed from Memory to save resources.

**``static void __exit``** to put the function **``hellodriver_exit``** ---> **.exit** section in memory , after executing that function it will be removed from Memory to save resources.

### 2. write Makefile
```Make
obj-m += hello.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
**``obj-m``** build as a dyanmic module (can load and unload)
, **``obj-y``** build as a static module (comiled as a part with zImage)

**``make -C /lib/modules/$(shell uname -r)/build``** ---> i want this make to use **Makefile** of the linux kernel. 

**``uname -r``** refers to ---> ``6.5.0-27-generic`` the version of linux in my device 

**``modules``** just do this task in the Makefile of the kernel

**``clean``** just do this task in the Makefile of the kernel

### 3. Build 
```
make
```
 - After that will appear the kernel module **hello.ko** that will be inserted to the kernel
 #### 4. use **``insmod``** command to insert the module to the kernel 
  ```bash
  sudo insmod hello.ko
  ```
  #### 5. using **(dmesg)** command to see the messages from kernel 
```bash
dmesg
```
it will print **``hello, world``** 
### 6. To remove the module from the kernel use ``rmmod`` 
```bash
sudo rmmod hello
```
### 7. Using ``dmesg``
```
dmesg
```
it will print **``Goodbye, world``** so it's the function executed when the driver removed from the kernel.
### Note: 
you have to put **\n** in **``printk()``** function
> Using **\n** in **printk()** ensures each log message appears on a new line in the kernel log file.
>
> Omitting **\n** may cause subsequent log messages to concatenate, making it hard to read the log file with dmesg.
>
> Including **\n** maintains clear and organized log output, aiding in effective debugging and system monitoring.
