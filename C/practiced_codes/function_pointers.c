/*
File: function_pointers.c
Description: Use function pointers for simple command dispatch.
*/


#include <stdio.h>


int add(int a,int b){return a+b;}
int sub(int a,int b){return a-b;}


int main(void) {
int (*op)(int,int);
op = add;
printf("5+3=%d\n", op(5,3));
op = sub;
printf("5-3=%d\n", op(5,3));
return 0;
}
