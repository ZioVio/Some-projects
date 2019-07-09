#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct string
{
    char * data;
    size_t length;
    size_t capacity;
} string;

string * String_alloc(const char * src);

void String_append(string * self, const char * src);

void String_free(string * self);

void String_fprint(FILE * stream, string * self); 

void String_print(string * self);
void String_println(string * self);
