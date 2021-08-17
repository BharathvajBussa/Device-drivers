#define MAGIC_NUMBER 'O'

struct cal {
	int x;
	int y;
	char z;
};

#define NAME_IOCTL_ADD  _IOWR(MAGIC_NUMBER , 8, struct cal)
#define NAME_IOCTL_SUB  _IOWR(MAGIC_NUMBER , 9, struct cal)
#define NAME_IOCTL_MUL  _IOWR(MAGIC_NUMBER , 10, struct cal)
#define NAME_IOCTL_DIV  _IOWR(MAGIC_NUMBER , 11, struct cal)
