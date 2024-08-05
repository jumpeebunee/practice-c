#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    int val;
    struct Node* next;
};

struct LinkedList {
    int size;
    bool empty;
    struct Node* head;
    struct Node* tail;
};

struct LinkedList* createLinkedList();

void push_front(struct LinkedList* list, int value);
void pop_front(struct LinkedList* list);
void push_back(struct LinkedList* list, int value);
void pop_back(struct LinkedList* list);

int size(struct LinkedList* list);
bool empty(struct LinkedList* list);

int value_at(struct LinkedList* list, int index);
void insert(struct LinkedList* list, int index, int value);
void erase(struct LinkedList* list, int index);
int reverse(struct LinkedList* list);

void main() {
    struct LinkedList* list = createLinkedList();

    printf("head: %d\n", list->head->val);
    printf("tail: %d\n", list->tail->val);
    printf("size: %d\n", size(list));
}

struct LinkedList* createLinkedList() {
    struct LinkedList* linkedList = (struct LinkedList*)malloc(sizeof(struct LinkedList*));
    linkedList->size = 0;
    linkedList->empty = true;

    return linkedList;
}

int reverse(struct LinkedList* list) {
    if (list->empty == true) return;

    struct Node* p = NULL;
    struct Node* c = list->head;
    struct Node* n = list->head->next;

    bool isFirst = true;

    while (c->next != NULL) {
       c->next = p;
       p = c;

       if (isFirst == true) {
        list->tail = c;
        isFirst = false;
       }

       c = n;
       n = n->next;
    }

    c->next = p;
    p = c;

    list->head = p;
}

void erase(struct LinkedList* list, int index) {
    if (list->size == 0 || index < 0 || index > list->size - 1) return;

    if (index == 0) {
        pop_front(list);
        return;
    } else if (index == list->size - 1) {
        pop_back(list);
        return;
    }

    struct Node* node = list->head;
    struct Node* prevNode = NULL;

    int i = 0;

    while (i != index) {
        prevNode = node;
        node = node->next;

        i++;
    }

    prevNode->next = node->next;
    free(node);
    node = NULL;

    list->size -= 1;
}

void insert(struct LinkedList* list, int index, int value) {
    if (index == 0) {
        push_front(list, value);
        return;
    }

    if (index < 0 || index > list->size - 1) return;

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    newNode->val = value;
    newNode->next = NULL;

    struct Node* node = list->head;
    struct Node* prev = NULL;

    int i = 0;

    while (i != index) {
        prev = node;
        node = node->next;

        i++;
    }

    newNode->next = node;
    prev->next = newNode;
    list->size += 1;
}

int value_at(struct LinkedList* list, int index) {
    if (list->empty == true || index > list->size - 1) return -1;

    struct Node* node = list->head;

    int i = 0;

    while (i != index) {
        node = node->next;
        i++;
    }

    return node->val;
}

int size(struct LinkedList* list) {
    return list->size;
}

bool empty(struct LinkedList* list) {
    return list->empty;
}

void push_front(struct LinkedList* list, int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->val = value;
    node->next = NULL;

    if (list->size == 0) {
        list->head = node;
        list->tail = node;

        list->empty = false;
    } else {
        node->next = list->head;
        list->head = node;  
    }

    list->size += 1;
}

void push_back(struct LinkedList* list, int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->val = value;
    node->next = NULL;

    if (list->empty == true) {
        list->head = node;
        list->tail = node;

        list->empty = false;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size += 1;
}

void pop_front(struct LinkedList* list) {
    if (list->empty == true) return;

    if (list->head->next == NULL) {
        list->head = NULL;
        list->tail = NULL;
    
        list->empty = true;
    } else {
        struct Node* temp = list->head;
        list->head = list->head->next;

        temp->next = NULL;
        free(temp);
        temp = NULL;
    }

    list->size -= 1;
}

void pop_back(struct LinkedList* list) {
    if (list->empty == true) return;

    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;

        list->empty = true;
    } else {
        struct Node* node = list->head;
        struct Node* prevNode = NULL;

        while (node->next != NULL) {
            prevNode = node;
            node = node->next;
        }

        prevNode->next = NULL;
        list->tail = prevNode;

        free(node);
        node = NULL;
    }

    list->size -= 1;
}