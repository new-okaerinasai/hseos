#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    if (v1 + v2 < v1) {
        return ~(uint32_t)0;
    } else {
        return v1 + v2;
    }
}