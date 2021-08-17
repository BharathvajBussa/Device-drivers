#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int num=10;
static char* charvar="Module";

module_param(charvar,charp,S_IRUGO);
module_param(num,int,S_IRUGO);

static int param_init(void)
{
	printk("In Init\n");
	printk("INT value:%d\n",num);
	printk("CHAR :%s\n",charvar);
	return 0;
}

static void param_cleanup(void)
{
	printk("Good Bye");
}

module_init(param_init);
module_exit(param_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("A module to use parameter");
