#include <stdio.h>
#include <string.h>

int main() {
    char arr[] = "charan"; //  change this string
    int len = strlen(arr);
    int isPalindrome = 1; // Flag to check palindrome

    for (int i = 0; i < len / 2; i++) {
        if (arr[i] != arr[len - 1 - i]) {
            isPalindrome = 0; // Not a palindrome
            break;
        }
    }

    if (isPalindrome) {
        printf("\"%s\" is a palindrome.\n", arr);
    } else {
        printf("\"%s\" is NOT a palindrome.\n", arr);
    }

    return 0;
}

