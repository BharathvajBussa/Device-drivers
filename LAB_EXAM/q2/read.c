#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd;
	char Kbuff[80];
	fd=open("/dev/MyCharDevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("\n error opening device");
		exit(1);
	}
	read(fd,Kbuff,50);
	printf("The data read from kernel is:\n %s \n",Kbuff);
	close(fd);
	return 0;
}
