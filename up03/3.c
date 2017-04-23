#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* new = malloc(len1 + len2 + 1);
    memcpy(new, str1, len1);
    memcpy(new + len1, str2, len2 + 1);
    return new;
}

struct Elem *process(struct Elem* head) {
    struct Elem *now = head;
    while (now != NULL) {
        int k = now->count - 1;
        now->count = 1;
        struct Elem* cur = now;
        struct Elem* old_next = now->next;
        for (int i = 0; i < k; ++i) {
            struct Elem* new = calloc(1, sizeof(*new));
            char tmp[20];
            sprintf(tmp, "-%d", i + 2); 
            new->count = 1;
            new->str = concat(now->str, tmp);
            cur->next = new;
            new->prev = cur;
            new->next = old_next;
            if (old_next) {
                old_next->prev = new;
            }
            cur = new;
        }
        now = old_next;
    }
    return head;
}
