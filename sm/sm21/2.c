#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile unsigned now = 0;
volatile unsigned n = 0;

void handler(int s) {
    printf("%u\n", now); fflush(stdout);
    ++n;
    if (n == 8) {
        exit(0);
    }
}

int isprime(unsigned a) {
    if (a == 1) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    for (unsigned i = 2; i * i <= a; ++i) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    unsigned high, low;
    scanf("%u %u", &low, &high);
    signal(SIGVTALRM, handler);
    struct itimerval itv = { .it_interval = { .tv_usec = 100000, .tv_sec = 0 },
                            .it_value = { .tv_usec = 100000, .tv_sec = 0 } };
    setitimer(ITIMER_VIRTUAL, &itv, NULL);
    for (unsigned i = low; i != high; ++i) {
        if (isprime(i)) {
            now = i;
        }
    }
    if (n != 8) {
        printf("-1\n"); fflush(stdout);
    }
}
