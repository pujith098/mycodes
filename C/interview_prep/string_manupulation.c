/*
File: string_manipulation.c
Description: Examples of string copy, reverse, and find (safe functions for embedded).
*/


#include <stdio.h>
#include <string.h>


void str_reverse(char *s) {
char *a = s, *b = s + strlen(s) - 1;
while (a < b) { char t = *a; *a++ = *b; *b-- = t; }
}


int main(void) {
char s[64] = "embedded-c";
printf("orig: %s\n", s);
str_reverse(s);
printf("rev : %s\n", s);
// safe copy
char dst[8];
snprintf(dst, sizeof(dst), "%s", "toolongstring");
printf("copied (truncated) : %s\n", dst);
return 0;
}
