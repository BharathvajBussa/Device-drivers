/* 2.Verify User Read/Write operations using IOCTL functionality */

//Include section
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
ssize_t NAME_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp);
ssize_t NAME_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp);
static long NAME_ioctl(struct file *filep,unsigned int cmd,unsigned long arg);

//structure that stores operations provided by the driver
struct file_operations fops =
{
	.owner=THIS_MODULE,
	.open=NAME_open,
	.read=NAME_read,
	.write=NAME_write,
	.release=NAME_release,
	.unlocked_ioctl=NAME_ioctl,
};

//structure for a character driver
struct cdev *my_cdev;
//structure to record data,size,recent activity
struct stats kdata;
///init function
static int __init Driver_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev=MKDEV(255,0);//create a device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("Major number is %d\n Minor number is %d\n",MAJOR,MINOR);
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

void __exit Driver_exit(void)
{
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\n Major number is %d\n Minor number is %d\n",MAJOR,MINOR);
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

ssize_t NAME_write(struct file *filep,const char __user *Ubuff,size_t count,loff_t *offp)
{
	char Kbuff[80];
	unsigned long result;
	ssize_t retval;
	result=copy_from_user((char *)Kbuff,(char *)Ubuff,count);
	if(result==0)
	{
		kdata.size=count;
		strcpy(kdata.buff,Kbuff);
		kdata.r_w=1;
		printk(KERN_ALERT "\n data written successfully\n");
		printk(KERN_ALERT "\n data written is \n <<%s>>\n",Kbuff);
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

//read function
ssize_t NAME_read(struct file *filep,char __user *Ubuff,size_t count,loff_t *offp)
{
	char Kbuff[]="Hello from Kernel";
	unsigned long result;
	ssize_t retval;
	result=copy_to_user((char *)Ubuff,(char *)Kbuff,sizeof(Kbuff));
	if(result==0)
	{
		kdata.size=strlen(Kbuff);
		strcpy(kdata.buff,Kbuff);
		kdata.r_w=0;
		printk(KERN_ALERT "\n Data read successfully\n");
		printk(KERN_ALERT "\n Data read is <<<%s>>\n",Ubuff);
		retval=sizeof(Kbuff);
		return retval;
	}
	else
	{
		printk(KERN_ALERT "\nError writing data	to user\n");
		retval=-EFAULT;
		return retval;
	}

}

static long NAME_ioctl(struct file *filep,unsigned int cmd,unsigned long arg)
{	int res;
	struct stats udata;
	switch(cmd)
	{
	case(GETSTATS):	
		/* res=copy_to_user(&kdata,(struct stat *)arg,sizeof(arg));
		 if(res==0)
		 {printk(KERN_ALERT "\n Status sent to application successfully");
		 }
		 */
		 printk(KERN_ALERT"\nSTATUS\n");
		 printk(KERN_ALERT "\nData: %s ",kdata.buff);
		 printk(KERN_ALERT "\nSize: %d ",kdata.size);
		 if(kdata.r_w==0)
		 { 
			 printk(KERN_ALERT "\nRead from Kernel i.e r_w=%d",kdata.r_w);
		 }
		 else if(kdata.r_w==1)
		 {
			 printk(KERN_ALERT "\n Written to KERNEL i.e r_w=%d",kdata.r_w);
		 }
		 else
		 {
			 printk(KERN_ALERT "\n NO tranmissions");
		 }
		 return 0;
	default: 
		printk("\n Invalid command\n");
		return -EINVAL;
	}
}

module_init(Driver_init);
module_exit(Driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bharathvaj");
MODULE_DESCRIPTION("a module to update status of transmission");

