#include "test_string_helper.h"
#include <stdlib.h>
#include <string.h>

char* generate_random_string(int length)
{
    if (length <= 0) return NULL;
    char *s = malloc(length + 1);
    if (!s) return NULL;

    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < length; i++)
        s[i] = charset[rand() % (sizeof(charset) - 1)];

    s[length] = '\0';
    return s;
}

char* generate_edge_case_empty_string(void)
{
    char *s = malloc(1);
    if (!s) return NULL;
    s[0] = '\0';
    return s;
}

char* generate_edge_case_single_char(char c)
{
    char *s = malloc(2);
    if (!s) return NULL;
    s[0] = c;
    s[1] = '\0';
    return s;
}

void free_string(char *s)
{
    free(s);
}
