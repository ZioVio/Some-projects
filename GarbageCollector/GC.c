#include "GC.h" 
#include "GCList.h" 
#include <stdio.h>


void GC_begin() {
    GCList_init(&listOfPtrs);
}
 
void GC_finish() {
    GCList_clear(&listOfPtrs);
    GCList_deinit(&listOfPtrs);
}

void * GC_malloc(size_t size) {
    void * ptr = malloc(size);
    GCList_add(&listOfPtrs, ptr);
    return ptr;
}

void * GC_realloc(void * ptr, size_t size) {
    int index = GCList_indexOf(&listOfPtrs, ptr);
    void * newPtr = realloc(ptr, size); 
    if (newPtr == NULL) {
        fprintf(stderr, "Error reallocating memory\n");
        abort();
    }
    ptr = newPtr;
    GCList_set(&listOfPtrs, index, ptr);
    return ptr;
}

void GC_free(void * ptr) {
    GCList_remove(&listOfPtrs, ptr);  
    free(ptr); 
}