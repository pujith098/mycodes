#include <stdio.h>
#include <limits.h>

int reverse_int(int x);  // forward declaration

void run_test(int x)
{
    int r = reverse_int(x);
    printf("Input:  %11d  -> Output: %11d\n", x, r);
}

int main(void)
{
    printf("\n=== Automatic Tests ===\n\n");

    // Edge cases
    run_test(0);
    run_test(5);
    run_test(-5);
    run_test(10);
    run_test(-10);

    // Regular numbers
    run_test(123);
    run_test(-123);
    run_test(1000);   // becomes 1
    run_test(-1200);  // becomes -21

    // Boundary cases near overflow
    run_test(1534236469);  // overflow -> 0
    run_test(-1563847412); // overflow -> 0

    // INT limits
    run_test(INT_MAX);
    run_test(INT_MIN);

    printf("\n=== Manual Test ===\n");
    printf("Enter an integer: ");
    int x;
    if (scanf("%d", &x) == 1) {
        printf("Reversed: %d\n", reverse_int(x));
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

