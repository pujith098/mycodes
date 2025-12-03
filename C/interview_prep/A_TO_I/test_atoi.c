#include <stdio.h>
#include <limits.h>
#include "atoi.h"

void run_test(int testNo, char *s) {
    int res = myAtoi(s);
    printf("=== TEST %d ===\n", testNo);
    printf("Input: \"%s\"\n", s);
    printf("Output: %d\n", res);
    printf("=================\n\n");
}

int main() {
    // Edge cases
    run_test(1, "42");
    run_test(2, "   -42");
    run_test(3, "4193 with words");
    run_test(4, "words and 987");
    run_test(5, "-91283472332"); // overflow negative
    run_test(6, "91283472332");  // overflow positive
    run_test(7, "0000000000012345678");
    run_test(8, "+1");
    run_test(9, "-0");
    run_test(10, "");             // empty string
    run_test(11, "   ");          // only spaces

    // Manual input
    char input[100];
    printf("Enter a string for manual test: ");
    if (scanf("%99s", input) == 1) {
        run_test(12, input);
    }

    return 0;
}

