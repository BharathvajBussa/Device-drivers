obj-m+=chardriver.o
KDIR=/lib/modules/$(shell uname -r)/build/
PWD :=$(shell pwd)
default:
	$(MAKE) -C$(KDIR) M=$(PWD) modules
	gcc -o application application.c
clean:
	$(MAKE) -C$(KDIR) M=$(PWD) clean
	rm application
