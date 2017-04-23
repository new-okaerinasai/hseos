#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("kek.txt", O_RDONLY);
    char buf[16];
    uint64_t a;
    read(fd, buf, 16);
    sscanf(buf, "%llu", &a);
    printf("%lld", a);
}