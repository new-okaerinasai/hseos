#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>

void* thread_fig(void* ptr) {
    int num;
    long long nw = 0;
    while (scanf("%d", &num) != -1) {
        nw += num;
        sched_yield();
    }
    return (void*)nw;
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    pthread_t* ids = calloc(n, sizeof(*ids));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != n; ++i) {    
        pthread_create(&ids[i], &attr, thread_fig, NULL);
    }
    long long s = 0;
    long long tmp;
    for (int i = 0; i != n; ++i) {
        pthread_join(ids[i], (void*)&tmp);
        s += tmp;
    }
    printf("%lld\n", s); fflush(stdout);
    free(ids);
}
