#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

int main() {
    int a, pid;
    scanf("%d", &pid);
    while(1) {
        scanf("%d", &a);
        if (a == -1) {
            kill(pid, SIGTERM);
        } else {
            kill(pid, SIGRTMIN + a);
        }
        printf("%s\n", strerror(errno));
    }
}