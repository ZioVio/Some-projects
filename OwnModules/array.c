#include <stdio.h> 
#include <stdlib.h>


typedef struct Array
{
    size_t size;
    int * elements;
} Array;

Array * createArray(size_t size) {
    Array * self = malloc(sizeof(Array));
    self -> size = size;
    self -> elements = (int*)malloc(sizeof(int) * size);
    return self;
}

void removeElem(Array * self, int index) {
    for (int i = index; i < self -> size - 1; i++) {
        self -> elements[i] = self -> elements[i + 1];
    }
    self -> elements = realloc(self -> elements, sizeof(self -> elements) * (self -> size - 1));
    self -> size--;
}

void push(Array * self, int num) {
    self -> elements = realloc(self -> elements, sizeof(self -> elements) * (self -> size + 1));
    self -> elements[self -> size] = num;
    self -> size++;
}

void pop(Array * self) {
    self -> elements = realloc(self -> elements, sizeof(self -> elements) * (self -> size - 1));
    self -> size--;
}

int  get(Array * self, int index) {
    return self -> elements[index];
}

void printArray(Array * self) {
    for (int i = 0; i < self -> size; i++) {
        printf("%d ", self -> elements[i]);
    }
    puts("");
}

void freeArray(Array * self) {
    free(self -> elements);
    free(self);
}

