#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    int val;
    struct Node* next;
};

struct Linked {
    struct Node* front;
    struct Node* back;
};

struct Linked* create_list() {
    struct Linked* list = (struct Linked*)malloc(sizeof(struct Linked));
    list->back = NULL;
    list->front = NULL;
    return list;
}

void add(struct Linked* q, int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;

    if (!q->front && !q->back) {
        q->front = node;
        q->front->next = q->front;
        q->back = q->front;
    } else {
        q->back->next = node;
        q->back = q->back->next;
        q->back->next = q->front;
    }
}

void rem(struct Linked* q) {
    if (!q->front && !q->back) return;
    
    if (q->front == q->back) {
        q->front = NULL;
        q->back = NULL;
    } else {
        q->front = q->front->next;
        q->back->next = q->front;
    }
}

void main() {
    struct Linked* q = create_list();
}