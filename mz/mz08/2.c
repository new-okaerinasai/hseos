#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int n = 0;
int now = 1;
int fds1[2], fds2[2], fds3[2];

void father() {
    close(fds2[1]); close(fds2[0]);
    close(fds1[0]); close(fds3[1]);
    if (now == 1) {
        printf("1 %d\n", now); fflush(stdout);
        ++now;
        write(fds1[1], &now, sizeof(now));
    }
    while (read(fds3[0], &now, sizeof(now)) > 0) {
        printf("1 %d\n", now); fflush(stdout);
        if (now == n) {
            _exit(0);
        }
        ++now;
        write(fds1[1], &now, sizeof(now));
    }
    _exit(0);
}

void son() {
    close(fds3[1]); close(fds3[0]);
    close(fds1[1]); close(fds2[0]);
    while (read(fds1[0], &now, sizeof(now)) > 0) {
        printf("2 %d\n", now); fflush(stdout);
        if (now == n) {
            _exit(0);
        }
        ++now;
        write(fds2[1], &now, sizeof(now));
    }
    _exit(0);
}

void gson() {
    close(fds1[1]); close(fds1[0]);
    close(fds3[0]); close(fds2[1]);
    while (read(fds2[0], &now, sizeof(now)) > 0) {
        printf("3 %d\n", now); fflush(stdout);
        if (now == n) {
            _exit(0);
        }
        ++now;
        write(fds3[1], &now, sizeof(now));
    }

    _exit(0);
}

int main(int argc, char* argv[]) {
    n = atoi(argv[1]);
    if (n == 1) {
        printf("1 1\n"); fflush(stdout);
        _exit(0);
    }
    pipe(fds1); pipe(fds2); pipe(fds3);
    if (!fork()) {
        if (!fork()) { gson(); }
        son();
    }
    father();
}
