#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

#include "array.h"

int main(int argc, char *argv[]) {
    int size = 10;
    Array * array = createArray(size);
    
    for (int i = 0; i < size; i++) {
        array -> elements[i] = i*i;
    }
    printArray(array);


    pop(array);
    pop(array);
    printf("%zu\n", array -> size);
    printArray(array);

    push(array, 10);
    push(array, 11);
    push(array, 11);
    push(array, 11);
    push(array, 11);
    printf("%zu\n", array -> size);
    printArray(array);

    removeElem(array, 0);
    removeElem(array, 4);
    printf("%zu\n", array -> size);
    printArray(array);

    printf("%d\n", get(array, 3));

    
    freeArray(array);


    return 0;
}