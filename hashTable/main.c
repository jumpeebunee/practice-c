#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    char* key;
    char* value;
    struct Node* next;
};

struct LinkedList {
    int size;
    struct Node* head;
};

struct HashTable {
    int size;
    int max;
    struct LinkedList** hash;
};

struct LinkedList* createLinkedList();
struct HashTable* createHashTable(int size);

struct Node* createNode(char* key, char* value);

bool addToLinkedList(struct LinkedList* l, char* key, char* value);

int hashValue(struct HashTable* h, char* key);
void add(struct HashTable* h, char* key, char* value);
char* get(struct HashTable* h, char* key);
void removeKey(struct HashTable* h, char* key);
void updateHashtable(struct HashTable* h, struct HashTable* newH);

void main() {
    struct HashTable* hash = createHashTable(3);
}

struct LinkedList* createLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));

    list->size = 0;
    list->head = NULL;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* hash = (struct HashTable*)malloc(sizeof(struct HashTable));

    hash->size = 0;
    hash->max = size;
    hash->hash = (struct LinkedList**)malloc(sizeof(struct LinkedList*) * size);

    for (int i = 0; i <= size; i++) {
        hash->hash[i] = createLinkedList();
    }

    return hash;
}

// Node

struct Node* createNode(char* key, char* value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;
}

// Linked List

bool addToLinkedList(struct LinkedList* l, char* key, char* value) {
    struct Node* node = createNode(key, value);

    bool isFinded = false;

    if (!l->head) {
        l->head = node;
    } else {
        struct Node* cur = l->head;
        struct Node* prev = NULL;

        while (cur) {
            if (cur->key == key) {
                cur->value = value;
                isFinded = true;
                break;
            }

            prev = cur;
            cur = cur->next;
        }

        if (!isFinded) {
            prev->next = node;
            l->size += 1;
        }
    }

    return isFinded;
}

// HashTable

int hashValue(struct HashTable* h, char* key) {
    int result = 0;

    for (int i = 0; i < strlen(key); i++) {
        result += key[i];
    }

    return result % h->max;
}

void add(struct HashTable* h, char* key, char* value) {
    int hashedValue = hashValue(h, key);

    if (h->max == h->size) {
        struct HashTable* newH = createHashTable(h->size * 2);
        updateHashtable(h, newH);

        add(newH, key, value);
        return;
    }

    bool isFinded = addToLinkedList(h->hash[hashedValue], key, value);

    if (!isFinded) {
        h->size += 1;
    }
}

char* get(struct HashTable* h, char* key) {
    int hashedValue = hashValue(h, key);

    if (!h->hash[hashedValue]) return NULL;

    struct Node* cur = h->hash[hashedValue]->head;
    struct Node* prev = NULL;

    while (cur) {
        if (cur->key == key) return cur->value;

        prev = cur;
        cur = cur->next;
    }

    return NULL;
}

void removeKey(struct HashTable* h, char* key) {
    int hashedValue = hashValue(h, key);

    if (!h->hash[hashedValue]) return;

    struct Node* cur = h->hash[hashedValue]->head;
    struct Node* prev = NULL;

    bool isFinded = false;

    while (cur) {
        if (cur->key == key) {
            if (!prev) {
                if (cur->next) {
                    h->hash[hashedValue]->head = cur->next;
                } else {
                    h->hash[hashedValue]->head = NULL;
                }
            } else {
                if (cur->next) {
                    prev->next = cur->next;
                } else {
                    prev->next = NULL;
                }
            }

            isFinded = true;
        };

        prev = cur;
        cur = cur->next;
    }

    if (isFinded) {
        h->hash[hashedValue]->size -= 1;
        h->size -= 1;
    }

}

bool has(struct HashTable* h, char* key) {
    int hashedValue = hashValue(h, key);

    if (!h->hash[hashedValue]) return false;

    struct Node* cur = h->hash[hashedValue]->head;
    struct Node* prev = NULL;

    while (cur) {
        if (cur->key == key) return true;

        prev = cur;
        cur = cur->next;
    }

    return false;
}

void updateHashtable(struct HashTable* h, struct HashTable* newH) {
    for (int i = 0; i < h->max; i++) {
        if (h->hash[i]->head) {
            struct Node* cur = h->hash[i]->head;
            struct Node* prev = NULL;

            while (cur) {
                add(newH, cur->key, cur->value);

                prev = cur;
                cur = cur->next;
            }
        }
    }

    h->hash = newH->hash;
    h->max = newH->max;
    h->size = newH->size;

    free(newH);
    newH = NULL;
}
