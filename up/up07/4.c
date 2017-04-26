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
    int pids[n + 1];
    int pid;
    int id = 0;
    for (int i = 0; i != n + 1; ++i) {
        pids[i] = -2;
    }
    for (int i = 1; i != n + 1; ++i) {
        pid = fork();
        if (!pid) {
            pids[i] = 0;
            id = i;
            break;
        }
    }
    int mp = a0 + (id - 1) * d;
    if (!pids[id]) {
        for (int now = id - 1; now <= (k - 1) * n + id - 1; now += n) {
            pwrite(fd, &mp, sizeof(mp), now * sizeof(int));
            mp += (n * d);
        }
    }
    close(fd);
    while (wait(NULL) > 0) { }
}
