#!/bin/bash
make
arm-linux-gnueabihf-gcc virtual_chrdev_app.c -o virtual_chrdev_app