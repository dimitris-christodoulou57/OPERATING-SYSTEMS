#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/sched.h>

static struct kobject *example_find_roots;
volatile int roots = 0;
struct task_struct *task;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	task = current;   //we use the global variable current in which there are the latest info about the latest process .
	printk("find_roots sysfs opened by process %d\n", task->pid);
	printk("id : %d, name: %s\n", task->pid, task->comm);
	do{
		task = task->parent; //we move the pointer to the parent process 
		printk("id : %d, name: %s\n", task->pid, task->comm);
	}while(task->pid != 1); //the loop finishes when we reach the init process with id=1
	return sprintf(buf, "id : %d\n", current->pid);
}

struct kobj_attribute foo_attribute = __ATTR(find_roots, 0660, foo_show, NULL);

static int __init find_roots_init (void)
{
	int error = 0;
	
	example_find_roots = kobject_create_and_add("teamXX", kernel_kobj);
	
	if (!example_find_roots)
		return (ENOMEM);

	error = sysfs_create_file(example_find_roots, &foo_attribute.attr);
	if (error) {
		printk("failed to create the foo file in /sys/kernel/kobject_example \n");
	}
	
	return error;
}

static void __exit find_roots_exit (void)
{
	
	printk("Module un initialized successfully \n");
	kobject_put(example_find_roots);
}

module_init(find_roots_init);
module_exit(find_roots_exit);
MODULE_LICENSE("GPL");	


