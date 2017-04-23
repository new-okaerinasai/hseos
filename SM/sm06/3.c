#include <stdio.h>
#include <stdint.h>

uint32_t convert(uint64_t a) {
    if (a > 0xFFFFFFFF) {
        return 0xFFFFFFFF;
    } else {
        return (uint32_t)a;
    }
}

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
    uint32_t result;
    uint64_t temp = (uint64_t)a * (uint64_t)b;
    if (n == 0) {
        return convert(temp);
    }
    uint64_t half_way = (uint64_t)1 << (n - 1);
    uint64_t half_way_mask = ((uint64_t)1 << n) - 1;
    if ((temp & half_way_mask) == half_way) {
        if (temp & ((uint64_t)1 << n)) {
            temp += (uint64_t)1 << (n - 1);
        }
    } else {
        temp += (uint64_t)1 << (n - 1);
    }
    result = convert(temp >> n);
    return result;
}
