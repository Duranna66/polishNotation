//
// Created by Wull Harm on 09.07.2023.
//

#ifndef P03D20_1_LIST_H
#define P03D20_1_LIST_H
struct data {
    char type;
    double value;
};
struct list {
    struct data x;
    struct list* next;
};
void listPrint(struct list* head);
struct list* listAdd(struct list* head, struct data value);
void listDestroy(struct list* head);
struct list* listPop(struct list* head);
struct list* listPush(struct list* head, struct data value);
#endif  // P03D20_1_LIST_H
