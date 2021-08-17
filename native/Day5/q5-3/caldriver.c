#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#include"ioctl.h"

#define NAME MyCharDevice

//function prototype
int NAME_open(struct inode *inode,struct file *filep);
int NAME_release(struct inode *inode,struct file *filep);
static long NAME_ioctl(struct file *filep,unsigned int cmd,unsigned long arg);

//structure that stores operations provided by the driver
struct file_operations fops =
{
	.owner=THIS_MODULE,
	.open=NAME_open,	
	.release=NAME_release,
	.unlocked_ioctl=NAME_ioctl,
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
	result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region
	if(result<0)
	{
		printk(KERN_ALERT "The Region requested is not obtainable\n");
		return(-1);
	}
	my_cdev=cdev_alloc();//allocate memory to chardev structure
	my_cdev->ops=&fops;//link fops to char device

	result=cdev_add(my_cdev,Mydev,1);//Notify kernel about new device
	if(result<0)
	{
		printk(KERN_ALERT "The Char device is not created\n");
		unregister_chrdev_region(Mydev,1);
		return(-1);
	}
	return 0;
}

//clean up function
void __exit CharDevice_exit(void)
{
	printk("\n Major number is %d\n Minor number is %d\n",MAJOR(Mydev),MINOR(Mydev));
	unregister_chrdev_region(Mydev,1);//unregister device number and device
	cdev_del(my_cdev);
	printk(KERN_ALERT "\nI have unregistered...\n");
}

//Open system call
int NAME_open(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In open system call\n");
	return 0;
}

//close system call
int NAME_release(struct inode *inode,struct file *filep)
{
	printk(KERN_ALERT "\n In close system call\n");
	return 0;
}

//ioctl function
static long NAME_ioctl(struct file *filep,unsigned int cmd,unsigned long arg)
{	
	int res;
	struct cal integer;
	switch(cmd)
	{
	case (NAME_IOCTL_ADD):	
			res=copy_from_user(&integer,(struct cal*)arg,sizeof(struct cal));
			if(res!=0)
			{ printk(KERN_ALERT "\n copy from user failed\n");
			  return -EFAULT;
			}
			printk(KERN_ALERT "\n Addition of %d and %d is: %d",integer.x,integer.y,(integer.x+integer.y));
			return 0;
	case (NAME_IOCTL_SUB):
			res=copy_from_user(&integer,(struct cal*)arg,sizeof(struct cal));
			if(res!=0)
			{printk(KERN_ALERT "\n copy from user failed\n");
			 return -EFAULT;
			}
			printk(KERN_ALERT "\n Subtraction of %d and %d is: %d",integer.x,integer.y,(integer.x-integer.y));
			return 0;
	case (NAME_IOCTL_MUL):
			res=copy_from_user(&integer,(struct cal*)arg,sizeof(struct cal));
			if(res!=0)
			{printk(KERN_ALERT "\n copy from user failed\n");
			 return -EFAULT;
			}
			printk(KERN_ALERT "\n Multiplication of %d and %d is: %d",integer.x,integer.y,((integer.x)*(integer.y)));
			return 0;
	case (NAME_IOCTL_DIV):
			res=copy_from_user(&integer,(struct cal*)arg,sizeof(struct cal));
			if(res!=0)
			{ printk(KERN_ALERT "\n copy from user failed\n");
			 return -EFAULT;
			}
			printk(KERN_ALERT "\n Division of %d and %d is: %d",integer.x,integer.y,(integer.x/integer.y));
			return 0;
	default:
			printk(KERN_ALERT "\nInvalid");
			return -EINVAL;
	}
}
module_init(CharDevice_init);
module_exit(CharDevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("a module to do operations passing a structure");
