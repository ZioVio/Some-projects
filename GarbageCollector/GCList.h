#pragma once

#include <stdlib.h>
#include <stdbool.h>


typedef struct __GCList GCList;
struct __GCList
{
    int capacity;
    int size;
    void **items;
};


void GCList_init(GCList *self);
void GCList_deinit(GCList *self);

void GCList_remove(GCList *self, void *value);

void GCList_set(GCList *self, int index, void *value);
void *GCList_get(GCList *self, int index);

int GCList_indexOf(GCList *self, void *value);

void GCList_add(GCList *self, void *value);

void GCList_clear(GCList *self);

