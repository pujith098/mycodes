#include "palindrome.h"
#include<stdlib.h>
#include<string.h>

/* Check if substring s[left..right] is a palindrome. */
int isPalindrome(char *s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

/* Returns malloc'ed longest palindromic substring */
char* longestPalindrome(char* s) {
    int n = strlen(s);
    
    if (n == 0) {
        char *ans = (char*)malloc(1);
        ans[0] = '\0';
        return ans;
    }

    int maxLen = 1;
    int start = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalindrome(s, i, j)) {
                int len = j - i + 1;
                if (len > maxLen) {
                    maxLen = len;
                    start = i;
                }
            }
        }
    }

    char *ans = (char*)malloc(maxLen + 1);
    strncpy(ans, s + start, maxLen);
    ans[maxLen] = '\0';
    return ans;
}

