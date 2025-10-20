/*
File: reverse_bits.c
Description: Reverse bits in a 32-bit unsigned integer.
Standalone example with main().
*/


#include <stdio.h>
#include <stdint.h>


uint32_t reverse_bits(uint32_t x) {
uint32_t r = 0;
for (int i = 0; i < 32; ++i) {
r <<= 1;
r |= (x & 1);
x >>= 1;
}
return r;
}


int main(void) {
uint32_t n = 0xF0F0A5A5; // example
printf("0x%08X -> 0x%08X\n", n, reverse_bits(n));
return 0;
}
