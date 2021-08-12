#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("A kernel module to take operator two integers and prints result");

int a=0;
int b=0;
static char* string="NO";
static char* addp="add";
static char* subp="sub";
static char* mulp="mul";
static char* divp="div";
//parameter declaration
module_param(string,charp,S_IRUGO);
module_param(a,int,S_IRUGO);
module_param(b,int,S_IRUGO);
//add function
static int add(int a,int b)
{
	return (a+b);
}
//subtraction function
static int sub(int a,int b)
{
	return (a-b);
}
//multiplication function
static int mul(int a,int b)
{
	return (a*b);
}
//division function
static int div(int a,int b)
{
	return (a/b);
}

static int hello_init(void)
{
  int c;
	if(strcmp(string,addp)==0)
	{ 
	c = add(a,b);
	printk(KERN_ALERT "Addition of %d and %d is:%d\n",a,b,c);
	}
	else if(strcmp(string,subp)==0)
	{
	c=sub(a,b);
	printk(KERN_ALERT "Subtraction of %d and %d is:%d\n",a,b,c);
	}
	else if(strcmp(string,mulp)==0)
	{
	c=mul(a,b);
	printk(KERN_ALERT "Multiplication of %d and %d is:%d\n",a,b,c);
	}
	else if(strcmp(string,divp)==0)
	{
	c=div(a,b);
	printk(KERN_ALERT "Division of %d and %d is:%d\n",a,b,c);
	}
	else
	{
	printk(KERN_ALERT "Invalid operator \n");
	}
return 0;
}
static void hello_cleanup(void)
{
	printk(KERN_ALERT "Good Bye\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

