#include<stdio.h>

int main()
{
    int num, rem, sum_digits =0, even_digits_sum =0, odd_digits_sum =0,digit_count = 0;
    printf("enter the number\n");

    scanf("%d",&num);

    while(num != 0)
    {
        rem = num % 10;
        if(digit_count & 1)
            odd_digits_sum += rem;
        else 
            even_digits_sum += rem;
        
        sum_digits += rem;

        num = num/10;
        digit_count ++;
    }
    printf("the sum of digits -%d \t odd sum is %d \t even sum is %d \t number of digit %d\n",sum_digits, odd_digits_sum,even_digits_sum,digit_count);
    return 0;
}

