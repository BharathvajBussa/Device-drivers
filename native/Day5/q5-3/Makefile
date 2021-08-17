obj-m+=caldriver.o
KDIR=/lib/modules/$(shell uname -r)/build/
PWD :=$(shell pwd)
default:
	$(MAKE) -C$(KDIR) M=$(PWD) modules
	gcc -o addapp addapp.c
	gcc -o subapp subapp.c
	gcc -o mulapp mulapp.c
	gcc -o divapp divapp.c
clean:
	$(MAKE) -C$(KDIR) M=$(PWD) clean
	rm addapp
	rm subapp
	rm mulapp
	rm divapp
