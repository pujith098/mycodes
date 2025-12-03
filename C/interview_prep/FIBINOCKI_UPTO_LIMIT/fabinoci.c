#include <stdio.h>

/*
 * Generate Fibonacci numbers up to (and below) a given limit.
 * Prints the sequence.
 */
void fabinoci(int limit)
{
    if (limit < 0) {
        printf("Invalid input: negative number.\n");
        return;
    }

    int n1 = 0, n2 = 1;

    // Print the first number
    printf("%d", n1);

    // Continue while next Fibonacci number is less than limit
    while (n2 < limit) {
        printf(", %d", n2);
        int temp = n1;
        n1 = n2;
        n2 = temp + n2;
    }

    printf("\n");
}

