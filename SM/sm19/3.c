#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int s1 = 0;
volatile int s2 = 0;

void handler(int s) {
    if (s == SIGUSR2) {
        ++s2;
    }
    if (s == SIGUSR1) {
        ++s1;
    }
    if (s == SIGTERM) {
        _exit(0);
    }
}

int main() {
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGTERM, handler);
    sigset_t ss, old;
    sigemptyset(&ss);
    sigaddset(&ss, SIGTERM);
    sigaddset(&ss, SIGUSR2);
    sigaddset(&ss, SIGUSR1);
    printf("%d\n", getpid());
    fflush(stdout);
    int s3 = s2;
    while(1) {
        sigprocmask(SIG_BLOCK, &ss, &old);
        sigsuspend(&old);
        if (s1 - s3 == 1) {
            printf("%d %d\n", s3, s2);
            s3 = s1;
            fflush(stdout);
        }
        sigprocmask(SIG_UNBLOCK, &ss, &old);
    }
}