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
        printf("%d %d\n", s1, s2);
        fflush(stdout);
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
    while(1) {
        sigprocmask(SIG_BLOCK, &ss, &old);
        sigsuspend(&old);
        sigprocmask(SIG_UNBLOCK, &ss, &old);
    }
}
