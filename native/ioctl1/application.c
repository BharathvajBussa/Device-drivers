#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<linux/ioctl.h>

#include"ioctl.h"

int main()
{
	int fd;
	char opt;
	long res;
	fd=open("/dev/MyCharDevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	printf("\nenter operator\n"); 
	scanf("%c",&opt);
	switch(opt)
	{
	case '+':
		res=ioctl(fd,NAME_IOCTL_ADD);
		break;
	case '-':
	        res=ioctl(fd,NAME_IOCTL_SUB);
		break;
 	case '*':
		res=ioctl(fd,NAME_IOCTL_MUL);
		break;
	case '/':
		res=ioctl(fd,NAME_IOCTL_DIV);
		break;
	default:
		printf("\ninvalid operator +,-,*,/ are allowed\n");
}	
	printf("\nuse dmesg to see Result\n");
	close(fd);
}
