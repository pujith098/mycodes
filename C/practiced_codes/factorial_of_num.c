#include<stdio.h>

int fact(int n)
{
	if(n == 0)
		return 1;
	return (n*fact(n-1));
}


int main()
{
	int num,res;
	printf("enter the number\n");
	scanf("%d", &num);
	res=fact(num);
	printf("fact of %d is - %d\n",num,res);
	
	return 0;
}
