#pragma once

#include "GCList.h"

GCList listOfPtrs; 

void GC_begin();

void GC_finish();

void * GC_malloc(size_t size);
void * GC_realloc(void * ptr, size_t size);
void   GC_free(void * ptr);