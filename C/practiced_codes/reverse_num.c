#include <stdio.h>

int reverse_method2(int n)
{
    int res = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        res = (res * 10) + rem;
        n = n / 10;
    }
    return res;
}

int reverse(int n)
{
    int res = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        res = (res * 10) + rem;
        n = n / 10;
    }
    return res;
}

int main()
{
    int num, rev1, rev2;

    printf("Enter the number: ");
    scanf("%d", &num);

    rev1 = reverse(num);
    rev2 = reverse_method2(num);

    printf("The reversed of %d using reverse() is: %d\n", num, rev1);
    printf("The reversed of %d using reverse_method2() is: %d\n", num, rev2);

    return 0;
}

