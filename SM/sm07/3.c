#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int value;
    int count;
    struct Node* next;
    struct Node* prev;
} Node;

Node* find (Node *head, int value) {
    Node* now = head;
    while (now != NULL) {
        if (now->value == value) {
            return now;
        }
        now = now->next;
    }
    return NULL;
}

int main() {
    int t;
    Node* head = NULL;
    Node* now;
    while (scanf("%d", &t) != -1) {
        now = find(head, t);
        if (now) {
            if (now == head) {
                now->count += 1;
            } else {
                now->prev->next = now->next;
                if (now->next) {
                    now->next->prev = now->prev;
                }
                now->next = head;
                now->prev = NULL;
                head->prev = now;
                now->count += 1;
                head = now;
            }
        } else {
            Node* temp = calloc(1, sizeof(*temp));
            temp->value = t;
            temp->count = 1;
            if (head) {
                temp->next = head;
                head->prev = temp;
                head = temp;
            } else {
                head = temp;
            }
        }
    }
    Node* end = head;
    while (head != NULL) {
        end = head;
        head = head->next;
    }
    while (end != NULL) {
        printf("%d %d\n", end->value, end->count);
        Node* tmp = end;
        end = end->prev;
        free(tmp);
    }
}
