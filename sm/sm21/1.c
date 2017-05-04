#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int s) {
    _exit(0);
}

int main() {
    struct timeval now = {};
    gettimeofday(&now, NULL);
    time_t s;
    signal(SIGALRM, handle);
    long ns;
    scanf("%ld, %ld", &s, &ns);
    long long future = (long long)s * 1000 + (long long)ns / 1000;
    long long tmp = future; //- ((long long)now.tv_sec * 1000 + now.tv_usec);
    if (tmp <= 0) {
        return 0;
    }
    struct timeval diff;
    diff.tv_sec = tmp / 1000;
    diff.tv_usec = (tmp % 1000) * 1000;
    struct itimerval new = {}, old = {};
    new.it_value = diff;
    printf("%ld\n", diff.tv_usec);
    setitimer(ITIMER_REAL, &new, &old);
    while (1) {
        pause();
    }
}
