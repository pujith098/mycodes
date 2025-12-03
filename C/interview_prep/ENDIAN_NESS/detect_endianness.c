#include "detect_endianness.h"
#include <stdint.h>

int is_little_endian(void) {
    uint16_t v = 0x0102;
    uint8_t *p = (uint8_t*)&v;
    return p[0] == 0x02;
}

// Generic for all architectures
const char* get_platform_endianness(void) {
    return is_little_endian() ? "little" : "big";
}

