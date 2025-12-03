#include <string.h>

/*
 * is_palindrome:
 *   Returns 1 if the string is a palindrome, 0 if not.
 *   Handles empty string and NULL safely.
 */
int is_palindrome(const char *s)
{
    if (s == NULL)
        return 0;

    int len = strlen(s);
    if (len < 2)
        return 1; // empty or single char is palindrome

    int i = 0, j = len - 1;

    while (i < j) {
        if (s[i] != s[j])
            return 0;
        i++;
        j--;
    }
    return 1;
}

