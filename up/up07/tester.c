#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sched.h>

int main() {
    int i;
    int fd = open("out.bin", O_RDONLY);
    while (read(fd, &i, sizeof(i)) > 0) {
        printf("%d\n", i);
    }
}