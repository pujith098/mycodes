#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "detect_endianness.h"

// Test: Compare manual memory check vs function output
void test_endianness_detection() {
    uint16_t v = 0x0102;
    uint8_t* p = (uint8_t*)&v;
    int expected = (p[0] == 0x02);
    int actual = is_little_endian();

    printf("[TEST] Expected: %s-endian\n", expected ? "little" : "big");
    printf("[TEST] Detected: %s-endian\n", actual ? "little" : "big");

    assert(expected == actual);
    printf("[PASS] Endianness detection is correct.\n\n");
}

// Exposed entry point for main()
void run_tests() {
    printf("Running endian tests...\n");
    test_endianness_detection();
}

