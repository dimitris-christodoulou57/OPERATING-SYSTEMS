obj-m := sysfs_module.o

KERNELDIR ?= /lib/modules/3.14.62-dev/build
PWD := /home/user/sysfs_module

default:
	$(MAKE) -C $(KERNELDIR) M=/home/user/sysfs_module modules

clean: 
	rm -f *.o *.ko *.mod.c
