#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle(int s) {
    _exit(0);
}

int main() {
    signal(SIGALRM, handle);
    struct timeval now = {};
    gettimeofday(&now, NULL);
    time_t s;
    long ns;
    scanf("%ld %ld", &s, &ns);
    long future = s * 1000 * 1000 + ns / 1000;
    long tmp = future - ((long)now.tv_sec * 1000 * 1000 + now.tv_usec);
    if (tmp <= 0) {
        return 0;
    }
    struct timeval diff;
    diff.tv_sec = tmp / 1000 / 1000;
    diff.tv_usec = tmp % 1000000;
    struct itimerval new = {};
    new.it_value = diff;
    setitimer(ITIMER_REAL, &new, NULL);
    while (1) {
        pause();
    }
}