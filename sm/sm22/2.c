#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void* thread_fig(void* ptr) {
    int num;
    pthread_t id;
    int nw = scanf("%d", &num);
    if (nw != -1) {
        pthread_create(&id, NULL, thread_fig, NULL);
        pthread_join(id, NULL);
        printf("%d\n", num);
    }
    return NULL;
}

int main() {
    pthread_t id;
    pthread_create(&id, NULL, thread_fig, NULL);
    pthread_join(id, NULL);
}
