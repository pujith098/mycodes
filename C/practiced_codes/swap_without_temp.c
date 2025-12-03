/*
File: swap_without_temp.c
Description: Swap two integers without a temporary using XOR and arithmetic variants.
*/


#include <stdio.h>


void swap_xor(int *a, int *b) {
if (a == b) return; // safe-guard when addresses equal
*a ^= *b;
*b ^= *a;
*a ^= *b;
}


int main(void) {
int x = 42, y = -17;
printf("Before: x=%d, y=%d\n", x, y);
swap_xor(&x, &y);
printf("After : x=%d, y=%d\n", x, y);
return 0;
}
