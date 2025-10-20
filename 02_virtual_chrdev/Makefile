obj-m += virtual_chrdev_driver.o

CURRENT_PATH := $(shell pwd)
KERNEL_PATH := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) clean