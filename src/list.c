#include "list.h"

#include <stdlib.h>
struct list* listAdd(struct list* head, struct data value) {
    if (head == 0) {
        head = malloc(sizeof(struct list));
        head->x = value;
        head->next = 0;
    } else {
        struct list* tmp = head;
        while (tmp->next != 0) {
            tmp = tmp->next;
        }
        tmp->next = malloc(sizeof(struct list));
        tmp->next->x = value;
        tmp->next->next = 0;
    }
    return head;
}
struct list* listPop(struct list* head) {
    if (head != 0) {
        struct list* tmp = head->next;
        free(head);
        head = tmp;
    }
    return head;
}
void listDestroy(struct list* head) {
    while (head != 0) {
        struct list* tmp = head->next;
        free(head);
        head = tmp;
    }
}
struct list* listPush(struct list* head, struct data value) {
    if (head == 0) {
        head = calloc(1, sizeof(struct list));
        head->x = value;
        head->next = 0;
    } else {
        struct list* t = calloc(1, sizeof(struct list));
        t->next = head;
        t->x = value;
        head = t;
    }
    return head;
}
