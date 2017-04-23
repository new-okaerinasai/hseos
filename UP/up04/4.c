#include <stdio.h>
#include <stdlib.h>
struct Node
{
    signed char value;
    struct Node *next;
};

extern struct Node* list_del(struct Node* head, int value);
/*struct Node* list_del(struct Node* head, int value) {
  	if (head == NULL) {
        return head;
    }
  	struct Node* current = head;
  	struct Node* previous = head;
  	while (current != NULL) {
    	  if (current->value == value) {
        	  previous->next = current->next;
            current = current->next;
        } else {
        	  previous = current;
            current = current->next;
        }
    }
    if (head->value == value) {
      head = head->next;
    }
    return head;
}
*/
int main() {
    struct Node* list1 = calloc(1, sizeof(*list1));
    struct Node* list2 = calloc(1, sizeof(*list2));
    struct Node* list3 = calloc(1, sizeof(*list3));
    struct Node* list4 = calloc(1, sizeof(*list4));
    struct Node* list5 = calloc(1, sizeof(*list4));
    list1->value = 1;
    list1->next = list2;
    list2->value = 3;
    list2->next = list3;
    list3->value = 2;
    list3->next = list4;
    list4->value = 1;
    list4->next = list5;
    list5->value = 1;
    list5->next = NULL;
    struct Node* head = list_del(list1, 1);
    while(head != NULL) {
      printf("%d\n",head->value);
      head = head->next;
    }
}