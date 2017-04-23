#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    unsigned short a;
    char* path = argv[1];
    int d = open(path, O_CREAT|O_TRUNC|O_WRONLY, 0600);
    char buf[2];
    while(scanf("%hu",&a) != -1) {
        buf[0] = a >> 8;
        buf[1] = a;
        write(d, buf, 2);
    }
    close(d);
}