#include <stdio.h>

int is_palindrome(const char *s); // forward declaration

void run_test(const char *s)
{
    printf("Input: \"%s\"  ->  %s\n",
           s,
           is_palindrome(s) ? "Palindrome" : "Not Palindrome");
}

int main(void)
{
    printf("\n=== Automatic Tests ===\n\n");

    run_test("charan");
    run_test("madam");
    run_test("racecar");
    run_test("abba");
    run_test("a");
    run_test("");
    run_test("abcba");
    run_test("abca");
    run_test("12321");
    run_test("123421");
    run_test("!@##@!");
    run_test("WasItACarOrACatISaw"); // case sensitive
    run_test("level");
    run_test("noon");

    printf("\n=== Manual Test ===\n");
    char s[200];

    printf("Enter a string: ");
    if (scanf("%199s", s) == 1) {
        printf("Result: %s\n",
               is_palindrome(s) ? "Palindrome" : "Not Palindrome");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

