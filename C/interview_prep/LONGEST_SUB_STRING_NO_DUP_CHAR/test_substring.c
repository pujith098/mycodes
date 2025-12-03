#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lengthOfLongestSubstring(char *s); // forward declaration

void run_test(int testNo, char *s) {
    int len = lengthOfLongestSubstring(s);
    printf("=== TEST %d ===\n", testNo);
    printf("Input string: \"%s\"\n", s);
    printf("Longest substring length: %d\n", len);
    printf("=================\n\n");
}

int main() {
    printf("=== Running Edge Case Tests ===\n\n");

    // Edge cases
    run_test(1, ""); // empty string
    run_test(2, "a"); // single char
    run_test(3, "aa"); // repeating chars
    run_test(4, "abcabcbb"); // example
    run_test(5, "bbbbb");
    run_test(6, "pwwkew");
    run_test(7, "abcdefg"); // unique chars
    run_test(8, "abba"); // palindrome like
    run_test(9, "dvdf"); // tricky repeating

    // Large random string
    char *longStr = malloc(100);
    for(int i=0; i<99; i++) longStr[i] = 'a' + (rand() % 26);
    longStr[99] = '\0';
    run_test(10, longStr);
    free(longStr);

    // Manual input
    char input[200];
    printf("Enter a string (manual test): ");
    if(scanf("%199s", input) == 1) {
        run_test(11, input);
    }

    return 0;
}

