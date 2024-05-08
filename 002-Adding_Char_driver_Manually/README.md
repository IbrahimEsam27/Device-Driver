# Adding Char device manually 

## Steps
### 1. check for unreserved number to give it to the dirver
```bash
cat /proc/devices
```
it list all major numbers of my drivers on my device , we choose number that is not reserved and i chose 50

### 2. Include Headers 
```c
#include <linux/fs.h>
#include <linux/moduleparam.h>
```
 - Using **``fs.h``** --> it has the operations on file (open,read,write,etc...)
 - Using **``moduleparam.h``** --> because i want to add the majour number manually as a parameter while inserting the module 
### 3. Adding init function
```c
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
``` 
#### Explaination of **``hellodriver_init``** :
 - **major_number** --> passed as a parameter manuaaly while insetrting and we choose number 50 because it's not used by any driver
 - **register_chrdev** --> This is the function we use to add driver manually and it takes Three Arguments (the major number, the driver name , pointer to a struct called file_operation)
>**file_operations** is a struct that have all operations done on our driver file (open , read , write , etc...) 

**``register_chrdev``** returns 0 if it successed to serve a driver and returns -1 if not.
### 4. create an object from **``file_operations``** struct
```c
struct file_operations fops =
    {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close};
```
**``.owner``** , **``.open``** and **``.release``** --> are pointers to a functions that execute specific task 
> **.open**: points to a function that do something while Openning the file we create for the driver
>
> **.releas**: points to a function that do something while Closing the file we create for the driver
### 5. write open and close functions
```c
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
```
### 6.delete the driver (major number) when usin **``rmmod``**
```c
static void __exit hellodriver_exit(void)
{
    unregister_chrdev(major_number, "mytest_driver");
    printk("GoodBye\n");
}
```
**unregister_chrdev** --> are used to delete the major number we served for our driver so we put it in the **exit** section to be executed when using **rmmod**
### 7. add the driver
``sudo insmod hello.ko number=50``
### 8. adding the driver under /dev/ Manually
`` sudo mknod /dev/test c 50 0``

This means add the driver who has **major number** = 50 , **minor number** = 0 and type **char** and name it **test** 
### 9. test the driver 
```bash
cat /dev/test
sudo dmesg
```
it will print the openning and closing meassages together and this hapeened becauese we didn't add **read** call back functions while using **file_operations** struct

``sudo dmesg``

```
driver_open dev_nr , open was called
driver_close dev_nr , closed was called
```
