#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR);
    int elems = atoi(argv[2]);
    double prev_in;
    read(fd, &prev_in, sizeof(prev_in));

    double cur_in;
    int written = 0;
    while(read(fd, &cur_in, sizeof(cur_in)) && written < elems - 1) {
        double now = cur_in - prev_in;
        lseek(fd, -sizeof(now), SEEK_CUR);
        write(fd, &now, sizeof(now));
        prev_in = now;
        ++written;
    }
}

