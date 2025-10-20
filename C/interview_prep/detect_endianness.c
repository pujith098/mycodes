/*
File: detect_endianness.c
Description: Detect system endianness at runtime.
*/


#include <stdio.h>
#include <stdint.h>


int is_little_endian(void) {
uint16_t v = 0x0102;
uint8_t *p = (uint8_t*)&v;
return p[0] == 0x02;
}


int main(void) {
printf("System is %s-endian\n", is_little_endian() ? "little" : "big");
return 0;
}
