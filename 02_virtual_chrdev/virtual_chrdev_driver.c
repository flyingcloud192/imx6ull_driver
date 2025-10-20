#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/idle.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harry Yan");
MODULE_DESCRIPTION("A simple Virtual Character Device Linux Kernel Module");

#define VIRTUAL_CHRDEV_NAME "virtual_chrdev"
#define VIRTUAL_CHRDEV_MARJOR 200

static char read_buffer[200];           // kernel data buffer
static char write_buffer[200];          // kernel data buffer
static char kernel_data[] = "Hello, this is data from the kernel virtual character device!";

/* open device */
static int virtual_chrdev_open(struct inode *inode, struct file *filp){
    return 0;
}

/* read data from device */
static ssize_t virtual_chrdev_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt){
    // copy kernel data to read buffer, then copy read_buffer to user space
    memcpy(read_buffer, kernel_data, sizeof(kernel_data));    
    if(copy_to_user(buf, read_buffer, cnt) == 0){
        printk(KERN_INFO "virtual_chrdev: copy to user success!\n");
    }
    else{
        printk(KERN_INFO "virtual_chrdev: copy to user failed!\n");
    }
    return 0;
}

/* write data to device */
static ssize_t virtual_chrdev_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt){
    // copy data from user space(buf) to kernel space write_buffer
    if(copy_from_user(write_buffer, buf, cnt) == 0){
        printk(KERN_INFO "virtual_chrdev: copy from user success! Data: %s\n", write_buffer);
    }
    else{
        printk(KERN_INFO "virtual_chrdev: copy from user failed!\n");
    }
    return 0;
}

/* close device */
static int virtual_chrdev_release(struct inode *inode, struct file *filp){
    return 0;
}

static struct file_operations test_fops = {
    .owner   = THIS_MODULE,
    .open    = virtual_chrdev_open,       // open device function
    .read    = virtual_chrdev_read,       // read data from device
    .write   = virtual_chrdev_write,      // write data to device
    .release = virtual_chrdev_release,    // close device function
};

static int __init virtual_chrdev_init(void){
    // register virtual_chrdev device with major number
    if (register_chrdev(VIRTUAL_CHRDEV_MARJOR, VIRTUAL_CHRDEV_NAME, &test_fops) < 0){
        printk(KERN_INFO "virtual_chrdev: register chrdev failed!\n");
        return -1;
    }
    else{
        printk(KERN_INFO "virtual_chrdev: register chrdev success!\n");
        return 0;
    }
}

static void __exit virtual_chrdev_exit(void){
    // unregister virtual_chrdev device
    unregister_chrdev(VIRTUAL_CHRDEV_MARJOR, VIRTUAL_CHRDEV_NAME);
    printk(KERN_INFO "virtual_chrdev: unregister chrdev success!\n");
}

moddule_init(virtual_chrdev_init);
module_exit(virtual_chrdev_exit);