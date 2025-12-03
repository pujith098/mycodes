#include <stdio.h>
#include "detect_endianness.h"

// Test runner from test_endianness.c
void run_tests();

int main(void) {
    printf("=== Platform Endianness Check ===\n");
    printf("Detected system is %s-endian\n\n", get_platform_endianness());

    // Run test suite
    run_tests();

    return 0;
}

