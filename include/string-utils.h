#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <stdlib.h>

/**
 * @brief Calculate the length of a string.
 * 
 * @param s the address of the string for which the length is calculated
 * @return size_t a number of characters corresponding to a length of a string
 */
size_t strlen(const char *s);

/**
 * @brief Replace a string with another.
 * 
 * @param src the address of the string to replace 
 * @param origin the address of the string at the origin of the replacement
 * @param replace the address of the string which replaces
 * @return char* an address of a string corresponding to a replaced string
 */
char *strreplace(char *src, char *origin, char *replace);
#endif