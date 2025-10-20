#include<stdio.h>
void swap(int *a, int *b)
{
	*a= *a + *b; //a = 10 + 30 = 40
	*b= *a - *b; //b = 40 - 30 = 10
	*a= *a - *b; //a = 40 - 10 = 30
}
void swap2(int *a , int *b)
{
	*a = *a ^ *b; // a = (1010 ^ 11110) = (10100) = 20
	*b =  *a ^ *b;	// b = (10100 ^ 11110) =  (01010)= 10
	*a =  *a ^ *b; // b = (10100 ^ 01010) = (11110) = 30      
}
int main()
{
	int a=10,b=30;
	printf("a- %d , b - %d\n",a,b);
	swap(&a,&b);

	printf("a- %d , b - %d\n",a,b);
	swap2(&a,&b);

	printf("a- %d , b - %d\n",a,b);

}

