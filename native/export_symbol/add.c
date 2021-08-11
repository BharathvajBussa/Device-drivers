#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("A kernel module to use export symbol");

static int my_add(int a,int b)
{
	printk(KERN_ALERT "In add function\n");
	return (a+b);
}

EXPORT_SYMBOL_GPL(my_add);

static int hello_init(void)
{
	printk(KERN_ALERT "hello in add module\n");
	return 0;
}

static void hello_clean(void)
{
	printk(KERN_ALERT "Good Bye in add module\n");
}

module_init(hello_init);
module_exit(hello_clean);
