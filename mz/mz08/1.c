#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

volatile int glob = 0;
volatile int now = 0;
volatile int old = 0;

void handler(int s) {
    old = glob;
    if (s == SIGUSR1) {
        glob += 2;
    } else if (s == SIGUSR2) {
        glob -= 3;

    }
    now = s;
}

int main() {
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    printf("%d\n", getpid()); fflush(stdout);
    while (1) {
        pause();
        printf("%d %d\n", now, old); fflush(stdout);
        if (glob < 0) {
            _exit(0);
        }
    }
}