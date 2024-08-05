#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Queue {
    int* queue;
    int writePointer;
    int size;
    int max;
    int pointer;
    int head;
};

struct Queue* createQueue(int size) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->queue = (int*)malloc(size * sizeof(int));

    queue->max = size;
    queue->pointer = -1;
    queue->size = -1;
    queue->head = 0;

    return queue;
}

int empty(struct Queue* q) {
    if (q->size == -1) return 1;
    return 0;
}

int full(struct Queue* q) {
    if (q->size == q->max - 1) return 1;
    return 0;
}

int buffer(struct Queue* q) {
    if (q->pointer == q->max - 1) return 1;
    return 0;
}

void enqueue(struct Queue* q, int value) {
    if (buffer(q)) {
        q->pointer = 0;
    } else {
        q->pointer += 1;
    }

    if (full(q)) {
        if (q->pointer == q->head) {
            if (buffer(q)) {
                q->head = 0;
            } else {
                q->head = q->pointer + 1;
            }
        }
    } else {
        q->size += 1;
    }

    q->queue[q->pointer] = value;
}

void dequeue(struct Queue* q) {
    if (empty(q)) return;
    
    q->size -= 1;
    q->queue[q->head] = 0;
    
    if (q->head == q->max - 1) {
        q->head = 0;
    } else {
        q->head += 1;
    }
}   

void main() {
    struct Queue* q = createQueue(4);
}