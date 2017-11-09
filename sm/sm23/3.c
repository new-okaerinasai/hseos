#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>

struct Item
{
    struct Item *next;
    long long value;
};

struct Item* _Atomic head = NULL;

void* thread_fig(void* n) {
    int begin = 1000 * (*(int*)n);
    for (int i = begin; i != begin + 1000; ++i) {
        struct Item* tmp = calloc(1, sizeof(*tmp));
        tmp->value = i;
        tmp->next = atomic_exchange(&head, tmp);
        sched_yield();
    }
    return NULL;
}

int main() {
    const int th = 100;
    pthread_t ids[th];
    int nums[th];
    for (int i = 0; i != th; ++i) {
        nums[i] = i;
        pthread_create(&ids[i], NULL, thread_fig, &nums[i]);
    }
    for (int i = 0; i != th; ++i) {
        pthread_join(ids[i], NULL);
    }
    struct Item* old_head = head;
    while (head != NULL) {
        printf("%lld\n", head->value);
        head = head->next;
    }
    while (old_head != NULL) {
        head = old_head;
        old_head = old_head->next;
        free(head);
    }
}
