#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
	int FileDesc;
	char Ubuff[]="User Buffer";
	char Kbuff[100];
	FileDesc=open("/dev/MyCharDevice",O_RDWR,0777);
	if(FileDesc<0)
	{
		printf("\n Error opening device\n");
		exit(1);
	}
	write(FileDesc,Ubuff,sizeof(Ubuff));
	read(FileDesc,Kbuff,50);
	printf("\nThe data read from kernel is\n <<<%s>>> \n",Kbuff);
	close(FileDesc);
}
