#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

void handler(int sig) {
    printf("%d\n", count); fflush(stdout);
    count++;
    if (count == 4) {
        _exit(0);
    }
}
int main() {
    printf("%d\n", getpid()); fflush(stdout);
    signal(SIGINT, handler);
    while(1) { pause(); }
}
