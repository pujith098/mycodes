#include "linked_list.h"
#include <time.h>

void genPalindrome(char *s, int maxLen) {
    int len = (rand() % maxLen) + 2;
    int half = len / 2;
    for (int i = 0; i < half; i++) {
        char c = 'a' + (rand() % 26);
        s[i] = s[len - 1 - i] = c;
    }
    if (len % 2) s[half] = 'a' + (rand() % 26);
    s[len] = '\0';
}

void genNearPalindrome(char *s, int maxLen) {
    genPalindrome(s, maxLen);
    int pos = rand() % maxLen;
    s[pos] = 'a' + (rand() % 26);
}

void genRandomNonPalindrome(char *s, int maxLen) {
    int len = (rand() % maxLen) + 3;
    for (int i = 0; i < len; i++)
        s[i] = 'a' + (rand() % 26);
    if (s[0] == s[len-1]) s[len-1] = ((s[len-1]-'a'+1)%26)+'a';
    s[len] = '\0';
}

void genPattern(char *s, int maxLen) {
    int len = (rand() % maxLen) + 4;
    char a = 'a' + (rand() % 26);
    char b = 'a' + (rand() % 26);
    for (int i = 0; i < len; i++)
        s[i] = (i % 2 == 0 ? a : b);
    s[len] = '\0';
}

void genSingle(char *s) {
    s[0] = 'a' + (rand() % 26);
    s[1] = '\0';
}

void generateRandomString(char *s, int maxlen) {
    int len = (rand() % maxlen) + 1;
    for (int i = 0; i < len; i++) s[i] = 'a' + (rand() % 26);
    s[len] = '\0';
}

void testString(int testNo, const char *str) {
    printf("\n=============================\n");
    printf("TEST %d\n", testNo);
    printf("Input string: %s\n", str);

    Node *head = buildListFromString(str);

    printf("Linked List: ");
    printList(head);

    int result = isPalindrome(head);

    if (result == -1) printf("Result: LOOP DETECTED ❌\n");
    else if (result == 1) printf("Result: PALINDROME ✔\n");
    else printf("Result: NOT PALINDROME ✘\n");

    printf("=============================\n");
}

int main() {
    srand(time(NULL));
    char s[200];

    int totalTests = 50;

    for (int i = 1; i <= totalTests; i++) {
        int type = rand() % 6;

        if (type == 0) genPalindrome(s, 20);
        else if (type == 1) genNearPalindrome(s, 20);
        else if (type == 2) genRandomNonPalindrome(s, 20);
        else if (type == 3) genPattern(s, 20);
        else if (type == 4) genSingle(s);
        else generateRandomString(s, 20);

        Node *head = buildListFromString(s);
        if (rand() % 10 == 0) {
            int pos = rand() % 5;
            createLoop(head, pos);
            printf("\n*** LOOP TEST (test %d) ***\n", i);
        }

        testString(i, s);
    }

    return 0;
}

