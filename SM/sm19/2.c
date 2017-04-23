#include <signal.h>
#include <stdio.h>
#include <unistd.h>
volatile int ok = 0;
void handler(int s) {
    if (s == SIGUSR1) {
        ok = 0;
    }
    if (s == SIGUSR2) {
        ok = 1;
    }
}

int main() {
    long long result = 0;
    printf("%d\n", getpid());
    fflush(stdout);
    signal(SIGUSR2, handler);
    signal(SIGUSR1, handler);
    int a;
    while (scanf("%d", &a) != -1) {
        if (ok) {
            result = a * a;
            printf("%lld\n", result);
            fflush(stdout);
        }
        else {
            result = -a;
            printf("%lld\n", result);
            fflush(stdout);
        }
    }
}
