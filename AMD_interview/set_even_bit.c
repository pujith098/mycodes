#include<stdio.h>

void set_even_bits(int *p)
{
	int temp=*p,highest_bit=-1;
	for(int i=0;i<32;i++)
	{
		if(temp & (1 << i))
			highest_bit=i;
	}

	for(int i=0;i<highest_bit;i+=2)
		temp |= (1 <<i);

	*p=temp;
}



int main()
{

	int var=45;
	set_even_bits(&var);

	printf("after the set ven bits %d", var);
	return 0;
}

