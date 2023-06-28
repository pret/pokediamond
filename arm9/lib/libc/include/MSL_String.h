#ifndef GUARD_MSL_STRING_H
#define GUARD_MSL_STRING_H

#include "ansi_params.h"
#include "size_t.h"

_MSL_BEGIN_NAMESPACE_STD
_MSL_BEGIN_EXTERN_C

void * memset(void *data, int value, size_t size);
void *memmove(void *dest, const void *src, size_t size);
void *memcpy(void *dest, const void *src, size_t size);
void *memchr(const void *arr, int value, size_t size);
int memcmp(const void *a, const void *b, size_t size);
signed char *strcpy(signed char *dest, const signed char *src);
unsigned strlen(const signed char *str);
signed char *strncpy(signed char *dest, const signed char *src, size_t n);
int strcmp(const signed char *a, const signed char *b);
signed char *strcat(signed char *dest, const signed char *src);
signed char *strncat(signed char *dest, const signed char *src, size_t n);
unsigned strspn(const signed char *a, const signed char *b);
signed char *strtok(signed char *str, const signed char *sep);
signed char *strstr(const signed char *haystack, const signed char *needle);

//todo this is literally the ugliest hack in existence and it's not gonna work always - this didn't work
//#define memset(mem, val, size) (val == 0 && __builtin_constant_p(size)) ? __builtin__clear(mem, size) : memset(mem, val, size)

_MSL_END_EXTERN_C
_MSL_END_NAMESPACE_STD

#endif //GUARD_MSL_STRING_H
