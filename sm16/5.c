#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sched.h>

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    void* mp = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    int* data = mp;
    data[0] = 1;
    int pid1 = fork();
    int pid2 = -2;
    if (pid1 > 0) {
        pid2 = fork();
    }
    while(data[0] != n + 1) {
        if (!pid1) {
            if (data[0] % 2 == 1) {
                printf("1 %d\n", data[0]); fflush(stdout);
                ++data[0];
            } else {
                sched_yield();
            }
        }
        else if (!pid2) {
            if (data[0] % 2 == 0) {
                printf("2 %d\n", data[0]); fflush(stdout);
                ++data[0];
            } else {
                sched_yield();
            }
        }
    }
    wait(NULL); wait(NULL);
}
