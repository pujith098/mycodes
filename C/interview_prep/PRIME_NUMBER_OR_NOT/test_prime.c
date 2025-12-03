// test_prime.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int is_prime(int n);   // from prime.c

void runTest(int testNo, int num) {
    printf("\n=============================\n");
    printf("TEST %d\n", testNo);
    printf("Input number: %d\n", num);

    int result = is_prime(num);

    if (result == 1)
        printf("Result: PRIME ✔\n");
    else
        printf("Result: NOT PRIME ✘\n");

    printf("=============================\n");
}

void runAllEdgeCases() {
    int testNo = 1;

    int edgeCases[] = {
        -100, -10, -1,   // negatives
         0,              // zero
         1,              // one (not prime)
         2,              // first prime
         3, 4, 5, 6, 7, 8, 9, 10, // small numbers
        97, 101, 103, 104, 105,   // random mids
        INT_MAX           // max int (a big prime candidate)
    };

    int count = sizeof(edgeCases) / sizeof(edgeCases[0]);

    printf("\n=== RUNNING EDGE CASE TESTS ===\n");

    for (int i = 0; i < count; i++) {
        runTest(testNo++, edgeCases[i]);
    }

    printf("\n=== EDGE CASE TESTS COMPLETED ===\n");
}

void runRandomTests(int totalTests) {
    printf("\n=== RUNNING RANDOM TESTS (%d) ===\n", totalTests);

    srand(time(NULL));
    for (int i = 1; i <= totalTests; i++) {
        int type = rand() % 3;
        int num;

        if (type == 0)
            num = rand() % 1000;         // small numbers
        else if (type == 1)
            num = (rand() % 2000000);    // mid-range
        else
            num = (rand() % INT_MAX);    // large numbers

        runTest(i, num);
    }

    printf("\n=== RANDOM TESTS COMPLETED ===\n");
}

int main() {
    runAllEdgeCases();
    runRandomTests(30);   // add more if you want

    return 0;
}

