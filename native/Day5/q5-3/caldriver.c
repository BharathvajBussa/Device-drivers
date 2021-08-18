#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include"caldriver.h"


int za;
int ud;
int zb;
int zc;
int zd;
//Add function prototype
int Add_open(struct inode *inode,struct file *filep);
int Add_release(struct inode *inode,struct file *filep);
ssize_t Add_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t Add_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
//Sub function prototypes
int Sub_open(struct inode *inode,struct file *filep);
int Sub_release(struct inode *inode,struct file *filep);
ssize_t Sub_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t Sub_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
//Mul function prototype
int Mul_open(struct inode *inode,struct file *filep);
int Mul_release(struct inode *inode,struct file *filep);
ssize_t Mul_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t Mul_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
//div function prototype
int Div_open(struct inode *inode,struct file *filep);
int Div_release(struct inode *inode,struct file *filep);
ssize_t Div_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t Div_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);

//structure that stores operations provided by the driver
struct file_operations fops =
{
	.owner=THIS_MODULE,
	.open=Add_open,
	.read=Add_read,
	.write=Add_write,	
	.release=Add_release,
};


//structure for a character driver
struct cdev *my_cdev;

//creating device number
dev_t Mydev=MKDEV(255,0);

//init function
static int __init CharDevice_init(void)
{
	int result;
	printk("Major number is %d\n Minor number is %d\n",MAJOR(Mydev),MINOR(Mydev));
	result=register_chrdev_region(Mydev,4,"Operation");//register device region
	if(result<0)
	{
		printk(KERN_ALERT "The Region requested is not obtainable\n");
		return(-1);
	}
	my_cdev=cdev_alloc();//allocate memory to chardev structure
	my_cdev->ops=&fops;//link fops to char device

	result=cdev_add(my_cdev,Mydev,4);//Notify kernel about new device
	if(result<0)
	{
		printk(KERN_ALERT "The Char device is not created\n");
		unregister_chrdev_region(Mydev,4);
		return(-1);
	}
	return 0;
}

//clean up function
void __exit CharDevice_exit(void)
{
	printk("\n Major number is %d\n Minor number is %d\n",MAJOR(Mydev),MINOR(Mydev));
	unregister_chrdev_region(Mydev,4);//unregister device number and device
	cdev_del(my_cdev);
	printk(KERN_ALERT "\nI have unregistered...\n");
}
//add read function
ssize_t Add_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp)
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

ssize_t Add_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp)
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

//Open system call 
int Add_open(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Add open system call\n");
	return 0;
}

//close system call
int Add_release(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Add close system call\n");
	return 0;
}

//sub open call
int Sub_open(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Sub open system call\n");
	return 0;
}
//sub close call
int Sub_release(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Sub close system call\n");
	return 0;
}
//mul open call
int Mul_open(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Mul open system call\n");
	return 0;
}
//mul close call
int Mul_release(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Mul close system call\n");
	return 0;
}
//div open call
int Div_open(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Div open system call\n");
	return 0;
}
//div close call
int Div_release(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In Div close system call\n");
	return 0;
}
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("a module to generate 4 device numbers and assign 1 arirthmetic operation to each device");
