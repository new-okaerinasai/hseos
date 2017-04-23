#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>

uint64_t sum = 0;
volatile int cur;
volatile int flag = 0;

void handler_sigterm(int s) {
    flag = 1;
}

void handler_main(int s) {
    cur = s - SIGRTMIN;
}

int main(int argc, char* argv[]) {
    int fds[argc];
    uint64_t sums[argc];
    for (int x = 0; x != argc; ++x) {
        signal(SIGRTMIN + x, handler_main);
    }
    sigset_t ss, old;
    sigemptyset(&ss);
    for (int x = 0; x != argc - 1; ++x) {
        sigaddset(&ss, SIGRTMIN + x);
    }
    sigaddset(&ss, SIGTERM);
    for (int i = 1; i != argc; ++i) {
        fds[i] = open(argv[i], O_RDONLY);
        sums[i] = 0;
    }
    printf("%d\n", getpid()); fflush(stdout);
    while (1) {
        sigprocmask(SIG_BLOCK, &ss, &old);
        sigsuspend(&ss);
        if (!flag) {
            char* buf[16];
            uint64_t a;
            read(fds[cur], buf, 16);
            sscanf(buf, "%lld", &a);
            sums[cur] += a;
        } else {
            for (int i = 0; i != argc; ++i) {
                printf("%lld\n", sums[i]); fflush(stdout);
            }
            _exit(0);
        }
        sisprocmask(SIG_UNBLOCK, &ss, &old);
    }
}
