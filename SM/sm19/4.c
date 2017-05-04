#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

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
    int64_t sums[argc];

    if (argc == 1) {
        _exit(0);
    }
    signal(SIGTERM, handler_sigterm);
    for (int x = 0; x != argc - 1; ++x) {
        signal(SIGRTMIN + x, handler_main);
    }=
    sigset_t ss, old;
    sigemptyset(&ss);
    for (int x = 0; x != argc - 1; ++x) {
        sigaddset(&ss, SIGRTMIN + x);
    }
    sigaddset(&ss, SIGTERM);

    for (int i = 0; i != argc - 1; ++i) {
        fds[i] = open(argv[i + 1], O_RDONLY);
        sums[i] = 0;
    }

    printf("%d\n", getpid()); fflush(stdout);
    while (1) {
        sigprocmask(SIG_BLOCK, &ss, &old);
        sigsuspend(&old);
        if (!flag) {
            char buf[16];
            int64_t a;
            if (read(fds[cur], buf, 16) == 16) {
                sscanf(buf, "%lld", &a);
                sums[cur] += a;
            } else {
                close(fds[cur]);
            }
        } else {
            for (int i = 0; i != argc - 1; ++i) {
                printf("%lld\n", sums[i]); fflush(stdout);
            }
            _exit(0);
        }
        sigprocmask(SIG_UNBLOCK, &ss, &old);
    }
}
