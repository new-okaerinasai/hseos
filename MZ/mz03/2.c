#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
        int value;
        int count;
        struct Node* next;
} Node;
    
Node* find(Node* head, int t) {
    Node* now = head;
    while (now != NULL) {
        if (now->value == t) {
            return now;
        }
        now = now->next;
    }
    return NULL;
}

void print(Node* head) {
    Node* now = head;
    while (now) {
        for (int i = 0; i != now->count; ++i) {
            printf("%d\n", now->value);
        }
        now = now->next;
    }
}

void delete(Node* head) {
    Node* now = head;
    while (now != NULL) {
        Node* tmp = now;
        now = now->next;
        free(tmp);
    }
}

int main() {
    int t;
    Node* head = NULL;
    Node* now;
    while (scanf("%d", &t) != -1) {
        if (!(now = find(head, t))) {
            Node* temp = calloc(1, sizeof(*temp));
            temp->next = head;
            temp->value = t;
            temp->count = 1;
            head = temp;
        } else {
            now->count++;
        }
    }
    print(head);
    delete(head);
}
