#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "GCList.h"

static void throwErr(const char * errmsg) {
    fprintf(stderr, "%s", errmsg);
    exit(EXIT_FAILURE);
}

static void GCList_realloc(GCList * self) {
    void * newPtr = realloc(self->items, sizeof(void*) * self -> capacity * 2);
    if (newPtr == NULL) {
        free(self->items);
        throwErr("Error realloccating memory\n");
    }
    self->items = newPtr;
    self->capacity *= 2;
}


void GCList_init(GCList *self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
    if (self->items == NULL)
    {
        throwErr("Error allocating memory\n");
    }
}
void GCList_deinit(GCList *self)
{
    free(self->items);
}

static size_t GCList_size(GCList *self)
{
    return self->size;
}
void *GCList_get(GCList *self, int index)
{
    if (index < 0 || index >= GCList_size(self))
        return NULL;
    return self->items[index]; 
}
void GCList_set(GCList *self, int index, void *value)
{
    if (index < 0 || index >= self->capacity)
        throwErr("Invalid index\n");
    self->items[index] = value;
}
void GCList_insert(GCList *self, int index, void *value)
{
    self->size += 1;
    if (self ->size >= self -> capacity) {
        GCList_realloc(self); 
    }
    for (int i = self -> size - 1; i > index; i--) {
        self->items[i] = self->items[i-1];
    }
    self->items[index] = value;
}
static void GCList_removeAt(GCList *self, int index)
{
    if (index < 0 || index >= self->capacity)
        throwErr("Invalid index\n");
    for (int i = index; i < self->size - 1; i++) {
        self->items[i] = self->items[i + 1];
    }
    self->size--;
}


void GCList_add(GCList *self, void *value)
{
    self->items[self->size] = value;
    self->size += 1;
    if (self ->size >= self -> capacity) {
        GCList_realloc(self); 
    }
}
    
int GCList_indexOf(GCList *self, void *value)
{
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == value)
            return i;
    }
    return -1;
}
void GCList_remove(GCList *self, void *value)
{
    int index = GCList_indexOf(self, value);
    if(index != -1){
        GCList_removeAt(self, index);
    }
}
bool GCList_contains(GCList *self, void *value)
{
    return GCList_indexOf(self, value) >= 0;
}
bool GCList_isEmpty(GCList *self)
{
    return self->size == 0;
}
void GCList_clear(GCList *self)
{
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == NULL)
            throwErr("Error freeing NULL\n");
        free(self->items[i]);
    }
    self->size = 0;
}

