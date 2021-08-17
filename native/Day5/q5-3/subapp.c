#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd,x,y;
	printf("\nenter two elements:");
	scanf("%d %d",&x,&y);
	fd=open("/dev/SubDev",O_RDWR,0777);
	if(fd<0)
	{printf("\n<<error>>"); }

	
	printf("\n<<<use sudo dmesg to see result>>>\n");
	close(fd);
}
