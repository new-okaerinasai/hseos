#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sched.h>

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    char* file = argv[2];
    int a0 = atoi(argv[3]);
    int d = atoi(argv[4]);
    int k = atoi(argv[5]);
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    ftruncate(fd, n * k * sizeof(int));
    for (int id = 0; id != n; ++id) {
        if (!fork()) {
            close(fd);
            fd = open(file, O_WRONLY);
            int mp = a0 + id * d;
            for (int now = id; now <= (k - 1) * n + id; now += n) {
                lseek(fd, now * sizeof(int), SEEK_SET);
                write(fd, &mp, sizeof(mp));
                mp += (n * d);
            }
            close(fd);
            _exit(0);
        }
    }
    while (wait(NULL) > 0) { }
}
