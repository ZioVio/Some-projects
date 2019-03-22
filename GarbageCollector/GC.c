#include "GC.h"
#include "list.h"
#include <stdio.h>


void GC_begin() {
    List_init(&listOfPtrs);
}

void GC_finish() {
    List_clear(&listOfPtrs);
    List_deinit(&listOfPtrs);
}

void * GC_malloc(size_t size) {
    void * ptr = malloc(size);
    List_add(&listOfPtrs, ptr);
    return ptr;
}

void * GC_realloc(void * ptr, size_t size) {
    int index = List_indexOf(&listOfPtrs, ptr);
    void * newPtr = realloc(ptr, size); 
    if (newPtr == NULL) {
        fprintf(stderr, "Error reallocating memory\n");
        abort();
    }
    ptr = newPtr;
    List_set(&listOfPtrs, index, ptr);
    return ptr;
}

void GC_free(void * ptr) {
    List_remove(&listOfPtrs, ptr);  
    free(ptr); 
}