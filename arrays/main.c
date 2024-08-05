#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>
#include "math.h"

typedef struct {
  int len;
  int cap;
  int* array;
} JAarray;

JAarray* jugged_array(int capacity) {
  JAarray* jArray = (JAarray*)malloc(sizeof(JAarray));
  jArray->array = malloc(capacity * sizeof(*jArray->array));

  jArray->cap = capacity;
  jArray->len = 0;

  return jArray;
}

void jugged_update(JAarray* jAarray) {
  jAarray->cap = jAarray->cap * 2;

  int* updatedArray = (int*)malloc(jAarray->cap * sizeof(int));

  for (int i = 0; i < jAarray->len; i++) {
    updatedArray[i] = jAarray->array[i];
  }

  free(jAarray->array);

  jAarray->array = updatedArray;
}

void check_jugged_full(JAarray* jAarray) {
  if (jAarray->len == jAarray->cap) {
    jugged_update(jAarray);
  }
} 

void jugged_push(JAarray* jAarray, int value) {
  check_jugged_full(jAarray);

  jAarray->array[jAarray->len] = value;
  jAarray->len += 1;
}

void jugged_pop(JAarray* jAarray) {
  if (jAarray->len == 0) return;

  jAarray->array[jAarray->len] = 0;
  jAarray->len -= 1;
}

void jugged_shift(JAarray* jAarray) {
  if (jAarray->len == 0) return;

  jAarray->len -= 1;

  for (int i = 0; i < jAarray->len; i++) {
    jAarray->array[i] = jAarray->array[i + 1];
  }
}

void jugged_unshift(JAarray* jAarray, int value) {
  check_jugged_full(jAarray);

  for (int i = jAarray->len; i >= 0; i--) {
    jAarray->array[i + 1] = jAarray->array[i];
  }

  jAarray->array[0] = value;
  jAarray->len += 1;
}

void jugged_concat(JAarray* jAarrayX, JAarray* jAarrayY) {
  for (int i = 0; i < jAarrayY->len; i++) {
    jugged_push(jAarrayX, jAarrayY->array[i]);
  }
}

bool jugged_every(JAarray* jAarray, bool func(int item, int index, JAarray* jAarray)) {
  if (jAarray->len == 0) return true;

  for (int i = 0; i < jAarray->len; i++) {
    int value = jAarray->array[i];
    if (!func(value, i, jAarray)) return false;
  }

  return true;
}

JAarray* jugged_filter(JAarray* jAarray, bool func(int item, int index, JAarray* jAarray)) {
  JAarray* filteredArray = jugged_array(4);

  for (int i = 0; i < jAarray->len; i++) {
    int value = jAarray->array[i];

    if (func(value, i, jAarray)) {
      jugged_push(filteredArray, value);
    }
  }

  return filteredArray;
}

int jugged_find(JAarray* jAarray, bool func(int item, int index, JAarray* jAarray)) {
  for (int i = 0; i < jAarray->len; i++) {
    int value = jAarray->array[i];

    if (func(value, i, jAarray)) return value;
  }

  return -1;
}

// Helpers
bool everyWithoutZero(int item, int index, JAarray* jAarray) {
  if (jAarray->array[0] == 0 || index > 15) return false;
}

bool isPrime(int item, int index, JAarray* jAarray) {
  for (int i = 2; item > i; i++) {
    if (item % i == 0) {
      return false;
    }
  }

  return item > 1;
}

// Testing
void filterTesting() {
  int mocked[17] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  JAarray* array = jugged_array(4);

  for (int i = 0; i < 17; i++) {
    jugged_push(array, mocked[i]);
  }

  JAarray* filteredArray = jugged_filter(array, isPrime);
}

void findTesting() {
  int mocked[4] = {4, 5, 8, 12};
  JAarray* array = jugged_array(4);

  for (int i = 0; i < 4; i++) {
    jugged_push(array, mocked[i]);
  }

  int findedInt = jugged_find(array, isPrime);
}

int main() {
  return 0;
}