// Embedded C Program: Simulated Register Access using readl() and writel()

#include <stdio.h>
#include <stdint.h>

// Simulate a memory-mapped register (in real systems, this would be a physical address)
volatile uint32_t fake_register = 0x00000000;

// Simulated base address (example: GPIO base address on BBB)
#define REG_BASE_ADDR ((volatile uint32_t *)&fake_register)

// Define readl and writel macros
#define readl(addr)        (*(volatile uint32_t *)(addr))
#define writel(value, addr) (*(volatile uint32_t *)(addr) = (value))

// Bit operation macros
#define SETBIT(data, bit_pos)    ((data) |  (1U << (bit_pos)))
#define CLEARBIT(data, bit_pos)  ((data) & ~(1U << (bit_pos)))
#define TOGGLEBIT(data, bit_pos) ((data) ^  (1U << (bit_pos)))

// Main
int main(void)
{
    uint32_t temp;

    printf("Initial Register Value: 0x%08X\n", readl(REG_BASE_ADDR));

    // Write a value to register
    writel(0xA5A5A5A5, REG_BASE_ADDR);
    printf("After writel(0xA5A5A5A5): 0x%08X\n", readl(REG_BASE_ADDR));

    // Read-modify-write to set bit 3
    temp = readl(REG_BASE_ADDR);
    temp = SETBIT(temp, 3);
    writel(temp, REG_BASE_ADDR);
    printf("After SETBIT(3): 0x%08X\n", readl(REG_BASE_ADDR));

    // Clear bit 5
    temp = readl(REG_BASE_ADDR);
    temp = CLEARBIT(temp, 5);
    writel(temp, REG_BASE_ADDR);
    printf("After CLEARBIT(5): 0x%08X\n", readl(REG_BASE_ADDR));

    // Toggle bit 7
    temp = readl(REG_BASE_ADDR);
    temp = TOGGLEBIT(temp, 7);
    writel(temp, REG_BASE_ADDR);
    printf("After TOGGLEBIT(7): 0x%08X\n", readl(REG_BASE_ADDR));

    return 0;
}

