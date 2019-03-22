#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "GC.h"

char * allocString(const char * s) {
    char * dst = GC_malloc(sizeof(char) * strlen(s) + 1);
    if (dst == NULL) {
        fprintf(stderr, "Error reallocating memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(dst, s); 
    return dst;
}

int main(int argc, char *argv[])
{
    GC_begin();
    int a = 15;
    int *x = NULL;

    x = GC_malloc(sizeof(int));

    *x = 14;

    x = &a;

    x = GC_malloc(sizeof(int));

    x = NULL;

    char *pstr = allocString("HEAP ME");

    int **par = GC_malloc(sizeof(int *) * 2);

    puts(pstr);

    *par = NULL;

    pstr = "READONLY";

    puts(pstr);
    GC_finish();
    return 0;
}