
/*
File: implement_memcpy.c
Description: Simple implementation of memcpy (does not handle overlapping regions).
*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>


void *simple_memcpy(void *dst, const void *src, size_t n) {
unsigned char *d = dst;
const unsigned char *s = src;
while (n--) *d++ = *s++;
return dst;
}


int main(void) {
char src[] = "Hello, memcpy!";
char dst[32];
simple_memcpy(dst, src, strlen(src) + 1);
printf("dst = %s\n", dst);
return 0;
}
