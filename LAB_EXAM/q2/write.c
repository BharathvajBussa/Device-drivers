#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd;
	char Ubuff[80];
	fd=open("/dev/MyCharDevice",O_RDWR,0777);
	printf("\n enter any string");
	scanf("%s",Ubuff);
	if(fd<0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	write(fd,Ubuff,sizeof(Ubuff));
	printf("\n The data is written\n");
	close(fd);
	return 0;
}
