#pragma once

#include <stdio.h> 
#include <stdlib.h>

typedef struct Array
{
    size_t size;
    int * elements;
} Array;

Array * createArray(size_t size);
void removeElem(Array * self, int index);
void push(Array * self, int num);
void pop(Array * self);
int get(Array * self, int index);
void printArray(Array * self);
void freeArray(Array * self);





