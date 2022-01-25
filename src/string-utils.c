#include <string.h>
#include <stdio.h>
#include "../include/string-utils.h"

size_t strlen(const char *s) {
    size_t size_string = 0;

    while (*s++ != '\0') {
        ++size_string;
    }

    return size_string;
}

char *strreplace(char *src, char *origin, char *replace) {
    char *buffer = malloc(1024 * sizeof(char));
    char *ptr;

    if(!(ptr = strstr(src, origin))) {
        buffer = src;
    } else {
        strncpy(buffer, src, ptr - src);
        buffer[ptr - src] = '\0';

        sprintf(buffer + (ptr - src), "%s%s", replace, ptr + strlen(origin));
    }

    return buffer;
}