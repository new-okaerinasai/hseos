#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int s1 = 0;
volatile int s2 = 0;

void handler(int s) {
    printf("lmao\n");
}

int main() {
    signal(SIGTERM, handler);
    sigset_t ss, old;
    sigemptyset(&ss);
    sigaddset(&ss, SIGTERM);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        sigprocmask(SIG_BLOCK, &ss, &old);
        sigsuspend(&old);
        sigprocmask(SIG_UNBLOCK, &ss, &old);
    }
}
