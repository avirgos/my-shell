#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H
#include <stdio.h>

struct string_vector {
    size_t capacity;
    size_t size;
    char **strings; 
};

void string_vector_init(struct string_vector *this, size_t capacity);
void string_vector_free(struct string_vector *this);
void string_vector_add(struct string_vector *this, const char *start, const char *end);
size_t string_vector_size(const struct string_vector *this);
char *string_vector_get(const struct string_vector *this, size_t index);
struct string_vector split_line(char *line);
char *str_join_array(char *dest, const struct string_vector *this, size_t first, size_t last, char *glue);
#endif