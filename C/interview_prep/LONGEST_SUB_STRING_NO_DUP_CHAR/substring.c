#include <stdlib.h>
#include <string.h>

typedef struct {
    int start;
    int end;
} Sub;

/*
 * generate_unique_substrings:
 *   For each character in the string, record the start and end of the
 *   substring ending at that character with unique characters.
 */
Sub *generate_unique_substrings(char *s, int *count) {
    int n = strlen(s);
    Sub *subs = malloc(n * sizeof(Sub));
    int idx = 0;

    int seen[256];
    int left = 0;

    for(int i=0; i<256; i++) seen[i] = -1;

    for (int right = 0; right < n; right++) {
        unsigned char c = s[right];

        if (seen[c] >= left)
            left = seen[c] + 1;

        seen[c] = right;

        subs[idx].start = left;
        subs[idx].end = right;
        idx++;
    }

    *count = idx;
    return subs;
}

/*
 * find_longest_length:
 *   Given all unique substrings' start/end positions, find the max length.
 */
int find_longest_length(Sub *subs, int count) {
    int maxlen = 0;
    for (int i = 0; i < count; i++) {
        int len = subs[i].end - subs[i].start + 1;
        if (len > maxlen)
            maxlen = len;
    }
    return maxlen;
}

/*
 * lengthOfLongestSubstring:
 *   Returns the length of the longest substring without repeating characters.
 */
int lengthOfLongestSubstring(char *s) {
    int count = 0;
    Sub *subs = generate_unique_substrings(s, &count);
    int ans = find_longest_length(subs, count);
    free(subs);
    return ans;
}

