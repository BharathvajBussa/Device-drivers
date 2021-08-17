#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"header.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("A module to export add and calculate average");
int x=1;
int y=1;

module_param(x,int,S_IRUGO);
module_param(y,int,S_IRUGO);
static int hello_init(void)
{
	int avg;
	avg= my_add(x,y)/2;
	printk(KERN_ALERT "Average is %d\n",avg);
	return 0;
}

static void hello_clean(void)
{
	printk(KERN_ALERT "Good Bye in Average module\n");
}

module_init(hello_init);
module_exit(hello_clean);
