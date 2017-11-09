#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int isprime(uint64_t a) {
    if (a == 1) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    if (a == 2) {
        return 1;
    }
    if (a % 2 == 0) {
        return 0;
    }
    for (uint64_t i = 3; i * i <= a; i += 2) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

uint64_t now = 0;

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
volatile int is = 0;

void* thread_fig(void* data) {
    uint64_t base = *((uint64_t*)data);
    while (1) {
        if (isprime(base)) {
            pthread_mutex_lock(&m);
            now = base;
            is = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
        }
        ++base;
    }
}

int main(int argc, char* argv[]) {
    uint64_t base, count;
    scanf("%lu %lu", &base, &count);
    pthread_t t1;
    pthread_create(&t1, NULL, thread_fig, (void*)&base);
    uint64_t n = 0;
    while (n < count) {
        pthread_mutex_lock(&m);
        if (is == 0) {
            pthread_cond_wait(&c, &m);
        }
        pthread_mutex_unlock(&m);
        
        printf("%lu\n", now);
        ++n;
        is = 0;
    }
}
