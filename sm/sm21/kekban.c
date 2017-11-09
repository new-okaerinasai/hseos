#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int s)
{
    printf("Alarmed\n");
}

int main(void)
{
    signal(SIGVTALRM, handler);
    struct itimerval itv = { .it_interval = { .tv_sec = 1 },
.it_value = { .tv_sec = 3 } };
    setitimer(ITIMER_VIRTUAL, &itv, NULL);
    while (1) {} //pause();
}
