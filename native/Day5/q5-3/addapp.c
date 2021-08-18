#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include"caldriver.h"

int main()
{
	int fd,z;
	struct str data;
	fd=open("/dev/AddDev",O_RDWR,0777);
	if(fd<0)
	{printf("\n<<error>>"); }
	printf("enter two numbers");
	scanf("%d%d",&data.x,&data.y);
	write(fd,&data,1);
	read(fd,&z,1);
	printf("\nAddition is %d \n",z);
	printf("\n<<<Result also available in kernel>>>\n");
	close(fd);
}
