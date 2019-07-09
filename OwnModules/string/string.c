#include "string.h"
#include <string.h>
#include <stdio.h>


static void String_realloc(string * self) {
    char * tmp = realloc(self->data, sizeof(char) * self->capacity * 2);
    if (tmp != NULL) {
        self->data = tmp;
    } else {
        free(self->data);
        printf("realloc error");
        abort();
    }
    self->capacity = self->capacity * 2;
} 

static void String_init(string * self,  const char * src) {
    size_t len = strlen(src);
    self->length = len;
    self->capacity = len + 1;
    self->data = malloc(sizeof(char) * self->capacity);
    memcpy(self->data, src, sizeof(char) * self->capacity);
}

string * String_alloc(const char * src) { 
    string * self = malloc(sizeof(string));
    String_init(self, src); 
    return self;
}

void String_append(string * self, const char * src) {
    size_t len = strlen(src);
    if (len + self->length + 1 >= self->capacity) {
        String_realloc(self); 
    }
    memcpy(self->data + self->length, src, sizeof(char) * (len + 1));
    self->length += len; 
}

static void String_deinit(string * self) {
    free(self->data);
}
void String_free(string * self) {
    String_deinit(self);
    free(self);
}

void String_fprint(FILE * stream, string * self) {
    fprintf(stream, "%s", self->data);
}

void String_print(string * self) {
    printf("%s", self->data);
}

void String_println(string * self) {
    puts(self->data);
}