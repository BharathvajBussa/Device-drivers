#define MAGIC_NUMBER 'O'

struct stats{
	int size;
	char buff[80];
	int r_w;
};

#define GETSTATS _IO(MAGIC_NUMBER,8)
