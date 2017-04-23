#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
	int fd = open("lmao.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	uint16_t buf[12];
	buf[0] = 1;
	buf[1] = 1;
	buf[2] = 5;
	buf[3] = 2;
	write(fd, buf, 8);
	return 0;
}