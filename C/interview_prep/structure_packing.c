/*
File: structure_packing.c
Description: Demonstrate structure packing and size differences using pragma.
*/


#include <stdio.h>
#include <stddef.h>


#pragma pack(push,1)
struct packed_s {
char a;
int b;
char c;
};
#pragma pack(pop)


struct normal_s {
char a;
int b;
char c;
};


int main(void) {
printf("sizeof(packed_s) = %zu\n", sizeof(struct packed_s));
printf("offsetof(b in packed_s) = %zu\n", offsetof(struct packed_s, b));
printf("sizeof(normal_s) = %zu\n", sizeof(struct normal_s));
printf("offsetof(b in normal_s) = %zu\n", offsetof(struct normal_s, b));
return 0;
}
