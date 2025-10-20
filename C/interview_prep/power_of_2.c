/*
 * Problem 2: Check if Number is Power of 2
 * Topic: Bit Manipulation, Algorithm Optimization
 * 
 * Interview Focus:
 * - Understanding binary representation
 * - Bit manipulation tricks
 * - Edge case handling (0, negative numbers)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Key Insight:
 * Powers of 2 have exactly ONE bit set in binary:
 * 1  = 0b0001
 * 2  = 0b0010
 * 4  = 0b0100
 * 8  = 0b1000
 * 16 = 0b10000
 * 
 * When you subtract 1 from a power of 2:
 * 8     = 0b1000
 * 8-1   = 0b0111
 * 8 & 7 = 0b0000 (Result is 0!)
 * 
 * For non-powers of 2:
 * 6     = 0b0110
 * 6-1   = 0b0101
 * 6 & 5 = 0b0100 (Result is NOT 0)
 */

// Method 1: Optimal bit manipulation trick
bool is_power_of_two(unsigned int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

// Method 2: Using subtraction trick (alternative)
bool is_power_of_two_v2(unsigned int n) {
    if (n == 0) return false;
    return (n & (n - 1)) == 0;
}

// Method 3: Count set bits (less efficient)
bool is_power_of_two_v3(unsigned int n) {
    if (n == 0) return false;
    
    int count = 0;
    while (n) {
        count += (n & 1);
        n >>= 1;
        if (count > 1) return false;
    }
    return count == 1;
}

// Method 4: Using modulo (not recommended for embedded - uses division)
bool is_power_of_two_v4(unsigned int n) {
    if (n == 0) return false;
    
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
}

// Bonus: Find next power of 2
uint32_t next_power_of_two(uint32_t n) {
    if (n == 0) return 1;
    
    // If already power of 2, return next one
    if ((n & (n - 1)) == 0) {
        return n << 1;
    }
    
    // Round up to next power of 2
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    
    return n;
}

// Bonus: Find previous power of 2
uint32_t prev_power_of_two(uint32_t n) {
    if (n == 0) return 0;
    
    // If already power of 2, return previous one
    if ((n & (n - 1)) == 0) {
        return n >> 1;
    }
    
    // Find highest set bit
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    
    return n - (n >> 1);
}

// Print binary representation
void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf("_");
    }
}

int main() {
    printf("=== Power of 2 Checker ===\n\n");
    
    // Test cases
    unsigned int test_cases[] = {
        0, 1, 2, 3, 4, 5, 8, 15, 16, 17, 
        32, 63, 64, 100, 128, 255, 256, 512, 1023, 1024
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("Number | Binary                              | Power of 2?\n");
    printf("-------|-------------------------------------|------------\n");
    
    for (int i = 0; i < num_tests; i++) {
        printf("%6u | ", test_cases[i]);
        print_binary(test_cases[i]);
        printf(" | %s\n", is_power_of_two(test_cases[i]) ? "YES" : "NO");
    }
    
    // Edge cases
    printf("\n=== Edge Cases ===\n");
    printf("0:          %s (Should be NO)\n", is_power_of_two(0) ? "YES" : "NO");
    printf("1:          %s (Should be YES - 2^0)\n", is_power_of_two(1) ? "YES" : "NO");
    printf("UINT_MAX:   %s (Should be NO)\n", is_power_of_two(UINT32_MAX) ? "YES" : "NO");
    
    // Performance comparison
    printf("\n=== Bonus Features ===\n");
    
    unsigned int test_nums[] = {5, 7, 15, 17, 100, 200};
    
    for (int i = 0; i < 6; i++) {
        printf("Number: %u\n", test_nums[i]);
        printf("  Next power of 2: %u\n", next_power_of_two(test_nums[i]));
        printf("  Prev power of 2: %u\n", prev_power_of_two(test_nums[i]));
    }
    
    // Real-world usage
    printf("\n=== Real-World Applications ===\n");
    printf("1. Memory alignment checks\n");
    printf("2. Buffer size validation (circular buffers should be power of 2)\n");
    printf("3. Hash table size optimization\n");
    printf("4. Fast modulo using (n & (size-1)) when size is power of 2\n");
    
    // Example: Fast modulo operation
    printf("\n=== Fast Modulo Example ===\n");
    uint32_t buffer_size = 16; // Must be power of 2
    uint32_t index = 25;
    
    if (is_power_of_two(buffer_size)) {
        uint32_t fast_mod = index & (buffer_size - 1);
        uint32_t slow_mod = index % buffer_size;
        printf("Buffer size: %u (power of 2)\n", buffer_size);
        printf("Index: %u\n", index);
        printf("Fast modulo (n & (size-1)): %u\n", fast_mod);
        printf("Slow modulo (n %% size):    %u\n", slow_mod);
        printf("Match: %s\n", (fast_mod == slow_mod) ? "YES" : "NO");
    }
    
    return 0;
}

/*
 * Interview Questions & Answers:
 * 
 * Q1: Why does (n & (n-1)) work?
 * A: When n is power of 2, it has exactly one bit set.
 *    Subtracting 1 flips all bits after that position.
 *    ANDing them gives 0 only if there was one bit set.
 * 
 * Q2: What about n=0?
 * A: 0 is NOT a power of 2 (by mathematical definition).
 *    That's why we need the (n != 0) check.
 * 
 * Q3: Is this faster than using loops?
 * A: Yes! This is O(1) - single instruction on most processors.
 *    Loop-based solutions are O(log n).
 * 
 * Q4: Can this work with signed integers?
 * A: Yes, but be careful with negative numbers.
 *    Negative numbers cannot be powers of 2.
 *    Use: return (n > 0) && ((n & (n-1)) == 0);
 * 
 * Q5: Real-world usage?
 * A: - Memory alignment checks
 *    - Validating buffer sizes for circular buffers
 *    - Fast modulo operations when divisor is power of 2
 *    - Hash table size validation
 * 
 * Q6: How to make buffer size a power of 2 if it's not?
 * A: Use next_power_of_two() function to round up.
 */
