// prime.c
#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
    if (n <= 1)
        return 0;   // 0 and 1 are NOT prime

    if (n == 2)
        return 1;   // 2 is prime

    if (n % 2 == 0)
        return 0;   // eliminate even numbers

    int limit = sqrt(n);  // only check up to sqrt(n)

    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

