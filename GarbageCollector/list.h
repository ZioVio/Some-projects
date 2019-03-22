#pragma once

#include <stdlib.h>
#include <stdbool.h>


typedef struct __List List;
struct __List
{
    int capacity;
    int size;
    void **items;
};


void List_init(List *self);
void List_deinit(List *self);

void * List_get(List *self, int index);
void List_remove(List *self, void *value);
void List_removeAt(List *self, int index);
void List_set(List *self, int index, void *value);

int List_indexOf(List *self, void *value);

size_t List_size(List * self);

void List_add(List *self, void *value);

void List_clear(List *self);

char * string_to_heap(const char * src);