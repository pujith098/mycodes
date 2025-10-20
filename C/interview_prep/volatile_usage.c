/*
File: volatile_usage.c
Description: Demonstrate volatile with a simulated hardware register and busy-wait.
*/


#include <stdio.h>
#include <stdint.h>


volatile uint32_t HW_STATUS = 0; // pretend hardware register


int main(void) {
// In another context (ISR / hardware) this would be changed.
// Simulate by changing after a few iterations.
for (int i=0;i<5;i++) {
if (i==3) HW_STATUS = 1; // simulate hardware event
while (!HW_STATUS) {
// busy-wait on volatile variable ensures compiler won't optimize away loop
// in real embedded code: sleep or low-power wait would be better
break; // break here so the example doesn't hang
}
printf("loop %d, status=%u\n", i, HW_STATUS);
}
return 0;
}
