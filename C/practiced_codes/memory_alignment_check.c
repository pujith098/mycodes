/*
File: memory_alignment_check.c
Description: Check pointer alignment for various types.
*/


#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


int is_aligned(void *ptr, size_t alignment) {
return ((uintptr_t)ptr & (alignment - 1)) == 0;
}


int main(void) {
int a;
void *p = &a;
printf("Pointer %p is %s4-byte aligned\n", p, is_aligned(p, 4) ? "" : "not ");
printf("Pointer %p is %s8-byte aligned\n", p, is_aligned(p, 8) ? "" : "not ");
return 0;
}
