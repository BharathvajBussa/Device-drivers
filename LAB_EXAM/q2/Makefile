obj-m+=IOCTL.o
KDIR=/lib/modules/$(shell uname -r)/build/
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o read read.c
	gcc -o write write.c
	gcc -o ioctlapp ioctlapp.c
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm read
	rm write
	rm ioapp
