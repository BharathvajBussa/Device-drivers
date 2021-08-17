#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int fd;
	struct cal input;
	int ret;
	printf("\nenter two elements:");
	scanf("%d %d",&input.x,&input.y);
	printf("\nenter any operator (+,-,*,/):");
	scanf(" %c",&input.z);
	fd=open("/dev/AddDev",O_RDWR,0777);
	if(fd<0)
	{printf("\n<<error>>"); }
	}
	printf("\n<<<use sudo dmesg to see result>>>\n");
	close(fd);
}
