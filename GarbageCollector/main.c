#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GC.h"

char *String_allocCopy(const char *src)
{
    char *dst = GC_malloc(sizeof(char) * strlen(src) + 1);
    if (dst == NULL)
    {
        fprintf(stderr, "Error reallocating memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(dst, src);
    return dst;
}

int main(int argc, char *argv[])
{
    GC_begin();
    size_t arrLen = 10;
    char **bufList = GC_malloc(sizeof(char *) * arrLen);
    int * someHeapedInt;
    for (int i = 0; i < arrLen; i++)
    {
        bufList[i] = String_allocCopy("ALWAYS ONE STRING HEAPED BUT 10 TIMES\n");
        someHeapedInt = GC_malloc(sizeof(int));
        *someHeapedInt = i;
        printf("%d ", *someHeapedInt);
    }
    void *ptr = GC_malloc(sizeof(size_t) * 4);
    ptr = NULL;

    int a = 15;
    int *x = NULL;

    x = GC_malloc(sizeof(int));
    *x = 14;
    x = &a;
    x = GC_malloc(sizeof(int));
    x = NULL;
    
    char *pstr = String_allocCopy("HEAP ME");
    int **par = GC_malloc(sizeof(int *) * 2);
    
    puts(pstr);
    *par = NULL;
    
    pstr = "READONLY";
    
    puts(pstr);

    GC_finish();
    return 0;
}










