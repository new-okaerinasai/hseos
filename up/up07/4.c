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
    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
    for (int id = 0; id != n; ++id) {
        if (!fork()) {
            int mp = a0 + id * d;
            for (int now = id; now <= (k - 1) * n + id; now += n) {
                pwrite(fd, &mp, sizeof(mp), now * sizeof(int));
                mp += (n * d);
            }
            _exit(0);
        }
    }
    close(fd);
    while (wait(NULL) > 0) { }
}
