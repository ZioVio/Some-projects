#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

static void throwErr(const char * errmsg) {
    fprintf(stderr, "%s", errmsg);
    exit(EXIT_FAILURE);
}

static void List_realloc(List * self) {
    void * newPtr = realloc(self->items, sizeof(void*) * self -> capacity * 2);
    if (newPtr == NULL) {
        free(self->items);
        throwErr("Error realloccating memory\n");
    }
    self->items = newPtr;
    self->capacity *= 2;
}



List * List_alloc()
{
    List * self = malloc(sizeof(List));
    List_init(self);
    return self;
}
void List_free(List *self)
{
    List_deinit(self);
    free(self);
}

void List_init(List *self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
    if (self->items == NULL)
    {
        throwErr("Error allocating memory\n");
    }
}
void List_deinit(List *self)
{
    free(self->items);
}

void *List_get(List *self, int index)
{
    if (index < 0 || index >= List_size(self))
        return NULL;
    return self->items[index]; 
}
void List_set(List *self, int index, void *value)
{
    if (index < 0 || index >= self->capacity)
        throwErr("Invalid index\n");
    self->items[index] = value;
}
size_t List_size(List *self)
{
    return self->size;
}
void List_insert(List *self, int index, void *value)
{
    self->size += 1;
    if (self ->size >= self -> capacity) {
        List_realloc(self); 
    }
    for (int i = self -> size - 1; i > index; i--) {
        self->items[i] = self->items[i-1];
    }
    self->items[index] = value;
}
void List_removeAt(List *self, int index)
{
    if (index < 0 || index >= self->capacity)
        throwErr("Invalid index\n");
    // void * toFree = self->items[index];
    for (int i = index; i < self->size - 1; i++) {
        self->items[i] = self->items[i + 1];
    }
    // if (toFree == NULL)
        // throwErr("Error freeing NULL\n");
    // free(toFree);
    self->size--;
}

void List_add(List *self, void *value)
{
    self->items[self->size] = value;
    self->size += 1;
    if (self ->size >= self -> capacity) {
        List_realloc(self); 
    }
}
    
int List_indexOf(List *self, void *value)
{
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == value)
            return i;
    }
    return -1;
}
void List_remove(List *self, void *value)
{
    int index = List_indexOf(self, value);
    if(index != -1){
        List_removeAt(self, index);
    }
}
bool List_contains(List *self, void *value)
{
    return List_indexOf(self, value) >= 0;
}
bool List_isEmpty(List *self)
{
    return self->size == 0;
}
void List_clear(List *self)
{
    for (int i = 0; i < self->size; i++) {
        if (self->items[i] == NULL)
            throwErr("Error freeing NULL\n");
        free(self->items[i]);
    }
    self->size = 0;
}


// char * String_allocCopy       (const char * src) {
//     char * dst = malloc(sizeof(char) * strlen(src) + 1);
//     if (dst == NULL) {
//         fprintf(stderr, "Error reallocating memory\n");
//         exit(EXIT_FAILURE);
//     }
//     strcpy(dst, src);
//     return dst;
// }
// char * String_allocFromInt    (int value) {
//     char buf[20];
//     buf[0] = '\0';
//     snprintf(buf, 100, "%d", value);
//     return String_allocCopy(buf);
// }
// char * String_allocFromDouble (double value) {
//     char buf[50];
//     buf[0] = '\0';
//     snprintf(buf, 100, "%f", value);
//     return String_allocCopy(buf);
// }