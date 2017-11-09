#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
enum { THR_N = 10 };
pthread_t ids[THR_N];

void* thread_fig(void* ptr) {
    int now = *((int*)ptr);
    if (now != 0) {
        pthread_join(ids[now - 1], NULL);
    }
    printf("%d\n", now); fflush(stdout);
    return NULL;
}

int main() {    
    int n[THR_N];
    for (int i = 0; i != THR_N; ++i) {
        n[i] = i;
        int err = pthread_create(&ids[i], NULL, thread_fig, &n[i]);
        if (err) {
            break;
        }
    }
    pthread_join(ids[THR_N - 1], NULL);
}
