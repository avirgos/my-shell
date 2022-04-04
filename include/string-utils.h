#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <stdlib.h>

/**
 * @brief Calculate the length of a string.
 * 
 * @param s address of the string for which the length is calculated
 * @return the number of characters corresponding to a length of a string
 */
size_t strlen(const char *s);

/**
 * @brief Replace a string with another.
 * 
 * @param src address of the string to replace 
 * @param origin address of the string at the origin of the replacement
 * @param replace address of the string which replaces
 * @return the address of a string corresponding to a replaced string
 */
char *strreplace(char *src, char *origin, char *replace);
#endif