#include <stdio.h>
#include <stdint.h>

uint32_t reverse_bits(uint32_t x); // forward declaration

void run_test(uint32_t x)
{
    uint32_t r = reverse_bits(x);
    printf("Input:  0x%08X\nOutput: 0x%08X\n\n", x, r);
}

int main(void)
{
    printf("=== Running automatic tests ===\n\n");

    // Edge cases
    run_test(0x00000000); // all zeros
    run_test(0xFFFFFFFF); // all ones
    run_test(0x00000001); // lowest bit
    run_test(0x80000000); // highest bit
    run_test(0xAAAAAAAA); // alternating
    run_test(0x55555555); // alternating
    run_test(0xF0F0A5A5); // random pattern
    run_test(0x12345678); // classic pattern
    run_test(0xDEADBEEF); // funny hex

    // Manual mode
    uint32_t x;
    printf("Enter a hex number (e.g., F0F0A5A5): 0x");
    if (scanf("%x", &x) == 1) {
        run_test(x);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}

