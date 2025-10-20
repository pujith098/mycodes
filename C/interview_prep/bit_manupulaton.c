/*
 * Problem 1: Bit Manipulation Macros
 * Topic: Register Operations, Hardware Control
 * 
 * Interview Focus:
 * - Understanding of bitwise operations
 * - Safe macro writing with proper parentheses
 * - Direct hardware register manipulation
 */

#include <stdio.h>
#include <stdint.h>

// Macros for bit manipulation
#define SET_BIT(reg, bit)     ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)  ((reg) ^= (1U << (bit)))
#define READ_BIT(reg, bit)    (((reg) >> (bit)) & 1U)

// Additional useful macros
#define SET_BITS(reg, mask)   ((reg) |= (mask))
#define CLEAR_BITS(reg, mask) ((reg) &= ~(mask))
#define TOGGLE_BITS(reg, mask) ((reg) ^= (mask))

// Write specific value to bit field
#define WRITE_BITS(reg, mask, value) \
    ((reg) = ((reg) & ~(mask)) | ((value) & (mask)))

// Extract bit field
#define READ_BITS(reg, mask, pos) \
    (((reg) & (mask)) >> (pos))

// Print binary representation (helper function)
void print_binary(uint32_t num) {
    printf("0b");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf("_");
    }
    printf(" (0x%08X)\n", num);
}

int main() {
    volatile uint32_t GPIO_PORT = 0x00000000;
    
    printf("=== Bit Manipulation Demo ===\n\n");
    
    printf("Initial value: ");
    print_binary(GPIO_PORT);
    
    // Set bit 5
    SET_BIT(GPIO_PORT, 5);
    printf("After SET_BIT(5): ");
    print_binary(GPIO_PORT);
    
    // Set bit 10
    SET_BIT(GPIO_PORT, 10);
    printf("After SET_BIT(10): ");
    print_binary(GPIO_PORT);
    
    // Clear bit 5
    CLEAR_BIT(GPIO_PORT, 5);
    printf("After CLEAR_BIT(5): ");
    print_binary(GPIO_PORT);
    
    // Toggle bit 10
    TOGGLE_BIT(GPIO_PORT, 10);
    printf("After TOGGLE_BIT(10): ");
    print_binary(GPIO_PORT);
    
    // Toggle it back
    TOGGLE_BIT(GPIO_PORT, 10);
    printf("After TOGGLE_BIT(10) again: ");
    print_binary(GPIO_PORT);
    
    // Set multiple bits
    SET_BIT(GPIO_PORT, 0);
    SET_BIT(GPIO_PORT, 3);
    SET_BIT(GPIO_PORT, 7);
    printf("After setting bits 0,3,7: ");
    print_binary(GPIO_PORT);
    
    // Read specific bits
    printf("\nReading individual bits:\n");
    printf("Bit 0: %u\n", READ_BIT(GPIO_PORT, 0));
    printf("Bit 3: %u\n", READ_BIT(GPIO_PORT, 3));
    printf("Bit 5: %u\n", READ_BIT(GPIO_PORT, 5));
    printf("Bit 7: %u\n", READ_BIT(GPIO_PORT, 7));
    
    // Real-world example: GPIO configuration
    printf("\n=== Real-World Example: GPIO Config ===\n");
    volatile uint32_t GPIO_CONFIG = 0x00000000;
    
    // Configure GPIO pins
    // Pin 0: Output (bit 0 = 1)
    // Pin 1: Input (bit 1 = 0)
    // Pin 2: Output (bit 2 = 1)
    SET_BIT(GPIO_CONFIG, 0);  // Pin 0 as output
    CLEAR_BIT(GPIO_CONFIG, 1); // Pin 1 as input (already 0)
    SET_BIT(GPIO_CONFIG, 2);  // Pin 2 as output
    
    printf("GPIO Config: ");
    print_binary(GPIO_CONFIG);
    
    // Using mask operations
    printf("\n=== Using Mask Operations ===\n");
    uint32_t PORT = 0x00000000;
    uint32_t MASK = 0x000000F0; // Bits 4-7
    
    SET_BITS(PORT, MASK);
    printf("After SET_BITS(0xF0): ");
    print_binary(PORT);
    
    CLEAR_BITS(PORT, 0x00000030); // Clear bits 4-5
    printf("After CLEAR_BITS(0x30): ");
    print_binary(PORT);
    
    return 0;
}

/*
 * Common Interview Questions:
 * 
 * Q1: Why use (1U << bit) instead of (1 << bit)?
 * A: To ensure unsigned arithmetic and avoid undefined behavior
 *    when shifting into sign bit of signed integers.
 * 
 * Q2: Why so many parentheses in macros?
 * A: To prevent operator precedence issues. Example:
 *    Without: SET_BIT(reg, 2+1) expands to reg |= 1 << 2+1 (wrong!)
 *    With: ((reg) |= (1U << (bit))) correctly evaluates bit first
 * 
 * Q3: What's the difference between |= and = |?
 * A: |= is compound assignment (modify in place)
 *    = | is assignment with OR (creates new value)
 * 
 * Q4: Can these macros be used with volatile registers?
 * A: Yes, and they should be for hardware registers to prevent
 *    compiler optimization issues.
 * 
 * Q5: What happens if bit position exceeds register size?
 * A: Undefined behavior! In production code, add bounds checking:
 *    #define SET_BIT_SAFE(reg, bit) \
 *        do { if ((bit) < 32) (reg) |= (1U << (bit)); } while(0)
 */
