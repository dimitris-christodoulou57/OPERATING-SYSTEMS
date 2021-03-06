DIMITRIS CHRISTODOULOU	AEM 2113 	dchristodoulou@uth.gr
VICTORIA BILIOURIS 	AEM 2138 	vbiliouri@uth.gr
GERASIMOS SIDERIS 	AEM 2275 	gsideris@uth.gr

PART1:

First of all, we created the file /usr/src/linux-3.14.62-dev/kernel/my_find_roots.c 

We added  my_find_roots.o in 13 line of /usr/src/linux-3.14.62-dev/kernel/Makefile

We added  asmlinkage long sys_find_roots(void); /usr/src/linux-3.14.62-dev/include/linux/syscalls.h

Finally, we defined the id of system call in /usr/src/linux-3.14.62-dev/arch/x86/syscalls/syscall_32.tbl as shown below
	354	i386	find_roots		sys_find_roots 

After we compiled the core:
sudo make
sudo make modules_install
sudo make install
checked if initrd.img-3.14.62-dev had created
sudo update-grud
restart

Then we copied the file unistd_32.h from /usr/src/linux-3.14.62-dev/arch/x86/include/generated/uapi/asm to /usr/include/i386-linux-gnu/asm

We compiled again the core:
sudo make
sudo make modules_install
sudo make install
checked if initrd.img-3.14.62-dev had created
sudo update-grud
restart

After all, we can use the system call

We created roots.c and roots.h	at home directory 

Then created libroots.a :

gcc -Wall -g -c -o libroots.o roots.c
ar rcs libroots.a libroots.o

After, we created find_roots_lib.c which compiles as below

gcc -Wall -g -c find_roots_lib.c -o find_roots_lib.o
gcc -g -o find_roots_lib_new find_roots_lib.o -L. libroots.a
./find_roots_lib_new

We wrote the command dmesg|tail in order to see the results of syscall my_find_roots.c 

NOTE: also you can see my_syscall.c and changes we made in order to implement as a example.

PART 2:

We copied the file noop-iosched.c to directory project1_module and renamed the file as project1-iosched.c. After we added the prefix "teamXX" in front of functions' name.

We created the Makefile to compile the module with command sudo make. 
We excuted the command sudo insmod project1-iosched.ko in order to insert module to core.

In order to use kernel module, we excuted the following command:
sudo bash -c "echo teamXX_noop>/sys/block/sda/queue/scheduler"
cat /sys/block/sda/queue/scheduler

Then we could see the results with command dmesg|tail.

In order to restore the scheduler and remove the kernel module, we excuted the following command:
sudo bash -c "echo cfq > /sys/block/sda/queue/scheduler"
rmmod project1_iosched.ko

PART 3:

We created the file sysfs_module.c at the directory sysfs_module.
We copied the example code and made some changes in order to implement find_root and kernel module create the sysfs file at /sys/kernel/teamXX/find_roots.
We changed the first argument at function kobject_create_and_add which make the visual folder. Then we changed the arguments of sysfs_create_file, kobject_put, module_init and module_exit. Finally, we added code to foo_show function in order to implements find_roots.

We created the Makefile in order to compile the sysfs.

In order to insert, run and delete the sysfs we excuted the following command:
insmod sysfs_module.ko
cat /sys/kernel/teamXX/find_roots
dmesg|tail
rmmod sysfs_module.ko
