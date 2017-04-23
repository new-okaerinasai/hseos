#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int fd = open(argv[1], O_RDONLY);
	double a;
	while(read(fd, &a, 8)) {
		printf("%.10g\n", a);
	}
}
