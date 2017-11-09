#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

volatile double m[3];
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_fig(void* p) {
    int* pp = (int*)p;
    for (int i = 0; i != 1000000; ++i) {
        pthread_mutex_lock(&counter_mutex);
        if (*pp == 0) {
            m[0] += 80;
            m[1] -= 90;
        } else if (*pp == 1) {
            m[1] += 100;
            m[2] -= 110;
        } else {
            m[2] += 120;
            m[0] -= 130;
        }
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int n1 = 0, n2 = 1, n3 = 2;
    pthread_create(&t1, NULL, thread_fig, &n1);
    pthread_create(&t2, NULL, thread_fig, &n2);
    pthread_create(&t3, NULL, thread_fig, &n3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    printf("%.10g %.10g %.10g\n", m[0], m[1], m[2]);
}
