#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

struct Data
{
    int16_t x; // 2 байта,
    int64_t y; // 8 байт
};

int main() {
	struct Data lmao[199];
	int fd = open("azaza1.txt", O_RDONLY);
	for (int i = 0; i != 1; ++i) {
		read(fd, &(lmao[i].x), 2);
		read(fd, &(lmao[i].y), 8);
	}

	for (int i = 0; i != 1; ++i) {
		printf("%d %ld\n", lmao[i].x, lmao[i].y);
	}
}
