#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s); // forward declaration
int isPalindrome(char *s, int left, int right);

void run_test(int testNo, char *s) {
    char *res = longestPalindrome(s);
    printf("=== TEST %d ===\n", testNo);
    printf("Input string: \"%s\"\n", s);
    printf("Longest Palindromic Substring: \"%s\"\n", res);
    printf("Length: %lu\n", strlen(res));
    printf("=================\n\n");
    free(res);
}

int main() {
    printf("=== Running Edge Case Tests ===\n\n");

    run_test(1, "");                 // empty string
    run_test(2, "a");                // single char
    run_test(3, "aa");               // two same chars
    run_test(4, "ab");               // two different chars
    run_test(5, "racecar");          // odd-length palindrome
    run_test(6, "babad");            // multiple possibilities
    run_test(7, "cbbd");             // even-length palindrome
    run_test(8, "abcdefg");          // no repeats
    run_test(9, "aabcdcb");          // internal palindrome
    run_test(10, "banana");          // multiple overlapping

    // Manual input
    char input[200];
    printf("Enter a string (manual test): ");
    if(scanf("%199s", input) == 1) {
        run_test(11, input);
    }

    return 0;
}

