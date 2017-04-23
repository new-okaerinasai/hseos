#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR);
    char n = 'a';
    char* mp = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    mp[1] = 'g';
    write(fd, &n, 1);
    printf("%s\n", mp);
}