#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<linux/ioctl.h>

#include"ioctl.h"
int main()
{
	int fd;
	struct cal input;
	int ret;
	fd=open("/dev/MyCharDevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	printf("\nenter two elements:");
	scanf("%d %d",&input.x,&input.y);
	printf("\nenter any operator (+,-,*,/):");
	scanf(" %c",&input.z);
	switch(input.z)
	{
	case '+':
		ret=ioctl(fd,NAME_IOCTL_ADD,&input);
		break;
	case '-':
	        ret=ioctl(fd,NAME_IOCTL_SUB,&input);
       		break;
	case '*':
		ret=ioctl(fd,NAME_IOCTL_MUL,&input);
		break;
	case '/':
		ret=ioctl(fd,NAME_IOCTL_DIV,&input);
		break;
	default:
		printf("\ninvalid");
		break;
	}
	printf("\n<<<use sudo dmesg to see result>>>\n");
	close(fd);
}
