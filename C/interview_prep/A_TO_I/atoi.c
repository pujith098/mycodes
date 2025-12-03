#include <limits.h>
#include "atoi.h"

/*
 * Converts a string to a 32-bit signed integer.
 * Handles optional leading spaces, +/-, leading zeros, non-digit chars.
 * Returns INT_MAX / INT_MIN on overflow.
 */
int myAtoi(char* s) {
    long num = 0;
    int i = 0, val, flag = 0;

    // Skip leading spaces
    while (s[i] == ' ')
        i++;

    // Check optional sign
    if (s[i] == '-') {
        flag = 1;
        i++;
    } else if (s[i] == '+') {
        i++;
    }

    // Skip leading zeros
    while (s[i] == '0')
        i++;

    // Convert digits
    while (s[i]) {
        char c = s[i];
        if (!(c >= '0' && c <= '9'))
            break;

        val = c - '0';

        // Check overflow
        if (!flag && num > (INT_MAX - val) / 10)
            return INT_MAX;
        if (flag && -num < (INT_MIN + val) / 10)
            return INT_MIN;

        num = num * 10 + val;
        i++;
    }

    if (flag)
        num = -num;

    return (int)num;
}

