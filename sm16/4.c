#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

void invoke(int parent) {
    int c; 
    int status;
    if (scanf("%d", &c) != -1) {
        int pid = fork();
        if (pid == -1) {
            printf("-1\n");
            exit(1);
        }
        if (!pid) {
            invoke(parent);
        }
        wait(&status);
        if (WEXITSTATUS(status) != 1) {
            fflush(stdout);
            printf("%d\n", c);
            exit(0);
        } else {
            if (parent == getppid()) {
                exit(0);
            } else {
                exit(1);
            }
        }
    } else {
        exit(0);
    }
}

int main() {
    int parent = getppid();
    invoke(parent);
}

