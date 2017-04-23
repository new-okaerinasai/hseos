#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fds1[2];
    int fds2[2];
    pipe(fds1);
    pipe(fds2);
    int max = atoi(argv[1]);
    int one = 1;
    write(fds2[1], &one, sizeof(one));
    if (!fork()) {
        int a;
        close(fds1[0]); close(fds2[1]);
        while (read(fds2[0], &a, sizeof(a))) {
            if (a == max) {
                _exit(0);
            }
            printf("1 %d\n", a); fflush(stdout);
            ++a;
            write(fds1[1], &a, sizeof(a));
        }
        _exit(0);
    } else if (!fork()) {
        int a;
        close(fds2[0]); close(fds1[1]);
        while (read(fds1[0], &a, sizeof(a))) {
            if (a == max) {
                _exit(0);
            }
            printf("2 %d\n", a); fflush(stdout);
            ++a;
            write(fds2[1], &a, sizeof(a));
        }
        _exit(0);
    }
    close(fds2[0]); close(fds2[1]);
    close(fds1[1]); close(fds1[0]);
    wait(NULL); wait(NULL);
    printf("Done\n");
}
