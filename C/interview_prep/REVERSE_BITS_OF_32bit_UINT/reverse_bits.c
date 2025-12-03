#include <stdint.h>

/*
 * reverse_bits:
 *   Reverses all 32 bits of a 32-bit unsigned integer.
 *
 * Optimized version using bit-twiddling hacks (faster than looping).
 */
uint32_t reverse_bits(uint32_t x)
{
    // Swap halfwords
    x = (x >> 16) | (x << 16);

    // Swap bytes
    x = ((x & 0xFF00FF00) >> 8) |
        ((x & 0x00FF00FF) << 8);

    // Swap nibble pairs
    x = ((x & 0xF0F0F0F0) >> 4) |
        ((x & 0x0F0F0F0F) << 4);

    // Swap bit pairs
    x = ((x & 0xCCCCCCCC) >> 2) |
        ((x & 0x33333333) << 2);

    // Swap individual bits
    x = ((x & 0xAAAAAAAA) >> 1) |
        ((x & 0x55555555) << 1);

    return x;
}

