#include "test_common.h"
#include <stdio.h>

static int total = 0, passed = 0;

void run_test(const char *name, test_func_t func) {
    printf("========================\n");
    printf("[INFO ] Running test: %s\n", name);
    total++;
    int result = func();
    if (result) {
        printf("[INFO ] Test passed: %s\n", name);
        passed++;
    } else {
        printf("[INFO ] Test FAILED: %s\n", name);
    }
    printf("========================\n");
}

void print_test_summary(void) {
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total: %d, Passed: %d, Failed: %d\n", total, passed, total - passed);
    printf("========================\n");
}

void print_array(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

