#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include"caldriver.h"
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//Add function prototype
int open_add(struct inode *inode,struct file *filep);
int release_add(struct inode *inode,struct file *filep);
ssize_t write_add(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t read_add(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);

//Sub function prototypes
int open_sub(struct inode *inode,struct file *filep);
int release_sub(struct inode *inode,struct file *filep);
ssize_t write_sub(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t read_sub(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
//Mul function prototype
int open_mul(struct inode *inode,struct file *filep);
int release_mul(struct inode *inode,struct file *filep);
ssize_t write_mul(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t read_mul(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
//div function prototype
int open_div(struct inode *inode,struct file *filep);
int release_div(struct inode *inode,struct file *filep);
ssize_t write_div(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t read_div(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
struct cdev *AddDev;
struct cdev *SubDev;
struct cdev *MulDev;
struct cdev *DivDev;
dev_t Mydev;
dev_t add;
dev_t sub;
dev_t mul;
dev_t div;
//init function
static int __init calculator_init(void)
{
	int result;
	result=register_chrdev_region(Mydev,4,"Operations");//register device region
	add=MKDEV(255,0);
	sub=MKDEV(255,1);
	mul=MKDEV(255,2);
	div=MKDEV(255,3);
	//memory allocation
	AddDev=cdev_alloc();
	SubDev=cdev_alloc();
	MulDev=cdev_alloc();
	DivDev=cdev_alloc();
	//linking fops
	AddDev->ops=&fops_add;
	SubDev->ops=&fops_sub;
	MulDev->ops=&fops_mul;
	DivDev->ops=&fops_div;
	int res_add;
	res_add=cdev_add(AddDev,Mydev,1);//Notify kernel about new device
	if(res_add<0)
	{
		printk(KERN_ALERT "\nThe add is not allocated\n");
		return(-1);
	}
	int res_sub;
	res_sub=cdev_sub(SubDev,Mydev,1);
	if(res_sub<0)
	{
		printk(KERN_ALERT "\nThe sub is not allocated\n");
		return (-1);
	}
	int res_mul;
	res_mul=cdev_mul(MulDev,Mydev,1);
	if(res_mul<0)
	{
		printk(KERN_ALERT "\n The mul is not allocated\n");
		return (-1);
	}
	int res_div;
	res_div=cdev_div(DivDev,Mydev,1);
	if(res_div<0)
	{
		printk(KERN_ALERT "\n The div is not allocated\n");
		return (-1);
	}
	return 0;
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//add read function
ssize_t read_add(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp)
{
	unsigned long result;
	ssize_t retval;
	result=copy_to_user(&ud,&za,sizeof(za));
	if(result==0)
	{
		printk(KERN_ALERT "\n Data read successfully\n");
		retval=sizeof(za);
		return retval;
	}
	else
	{
		printk(KERN_ALERT "\nError writing data	to user\n");
		retval=-EFAULT;
		return retval;
	}

}

ssize_t write_add(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp)
{
	unsigned long result;
	ssize_t retval;
	struct str kd;
	result=copy_from_user(&kd,&ud,count);
	if(result==0)
	{	za=kd.x+kd.y;
		printk(KERN_ALERT "\n Addition is %d \n",za);
		retval=count;
		return retval;
	}
	else
	{
		printk(KERN_ALERT "\n Error writing data\n");
		retval=-EFAULT;
		return retval;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Open system call 
int open_add(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Add open system call\n");
	return 0;
}

//close system call
int release_add(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Add close system call\n");
	return 0;
}

//sub open call
int open_sub(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Sub open system call\n");
	return 0;
}
//sub close call
int release_sub(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Sub close system call\n");
	return 0;
}
//mul open call
int open_mul(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Mul open system call\n");
	return 0;
}
//mul close call
int release_mul(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Mul close system call\n");
	return 0;
}
//div open call
int open_div(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Div open system call\n");
	return 0;
}
//div close call
int release_div(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Div close system call\n");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//clean up function
static void calculator_clean(void)
{
	//delete the device locations
	cdev_del(AddDev);
	cdev_del(SubDev);
	cdev_del(MulDev);
	cdev_del(DivDev);
	cdev_del(Mydev);
	//unregister from the kernel space
	unregister_chrdev_region(my_device_number, 4);
	printk(KERN_ALERT "I have unregistered\n");
}

module_init(calculator_init);
module_exit(calculator_clean);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("a module to generate 4 device numbers and assign 1 arirthmetic operation to each device");
