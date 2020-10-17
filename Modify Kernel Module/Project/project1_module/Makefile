obj-m := project1-iosched.o

KERNELDIR ?= /lib/modules/3.14.62-dev/build
PWD := /home/user/project1_module

default:
	$(MAKE) -C $(KERNELDIR) M=/home/user/project1_module modules

clean: 
	rm -f *.o *.ko *.mod.c
