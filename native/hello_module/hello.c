#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk(KERN_ALERT "Hello_world\n");
	return 0;
}

static void hello_cleanup(void)
{
	printk("Good Bye\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("A Simple Hello world kernel module");
