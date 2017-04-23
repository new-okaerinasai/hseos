#include <stdio.h>
#include <stdlib.h>


int main() {
    typedef struct Node {
        int elem;
        struct Node* next;
    } Node;
    int t;
    Node* head = NULL;
    while (scanf("%d", &t) != -1) {
        Node *temp = calloc(1, sizeof(*temp));
        temp->elem = t;
        temp->next = head;
        head = temp;
    }
    Node* now = head;
    while (now != NULL) {
        printf("%d\n", now->elem);
        now = now->next;
    }
    now = head;
    while (now != NULL) {
        Node* temp = now;
        now = now->next;
        free(temp);
    }
}
