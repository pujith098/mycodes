#include <limits.h>

/*
 * reverse_int:
 *   Reverses a signed 32-bit integer.
 *   Handles overflow safely and returns 0 on overflow.
 */
int reverse_int(int x)
{
    int num = 0;

    while (x != 0) {
        int rem = x % 10;
        x /= 10;

        // Check positive overflow
        if (num > INT_MAX / 10 || (num == INT_MAX / 10 && rem > 7))
            return 0;

        // Check negative overflow
        if (num < INT_MIN / 10 || (num == INT_MIN / 10 && rem < -8))
            return 0;

        num = num * 10 + rem;
    }

    return num;
}

