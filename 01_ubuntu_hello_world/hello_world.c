#include <linux/moudle.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harry Yan");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module on Ubuntu");

static int __init hello_world_init(void){
    printk(KERN_INFO "Hello, World! This is my first Linux Kernel Module on Ubuntu.\n");
    return 0;
}

static void __exit hello_world_exit(void){
    printk(KERN_INFO "Goodbye, World! Exiting my first Linux Kernel Module on Ubuntu.\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);