#include<stdio.h>

int is_prime(int);

int is_prime(int n)
{
	if(n<=0) {
		printf("invalid input\n");
		return 0;
	}
	else if(n==1)
		return 0;
	else if (n== 2)
		return 1;
	for(int i=2;i<=n/2;i++)
	{
		if(n%i == 0)
			return 0;
	}
	return  1;
}

int main()
{
	int num, res;
	printf("enter the number\n");
	scanf("%d",&num);
	if(is_prime(num))
		printf("the given number is prime\n");
	else
		printf("its a not a prime\n");

	
	return 0;
}


