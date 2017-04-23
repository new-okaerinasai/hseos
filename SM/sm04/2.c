#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t v;
    if (__builtin_add_overflow(v1, v2, &v)) {
        int32_t max = (~(uint32_t)0) >> 1;
        int32_t min = (uint32_t)max + 1;
        if (v < v1) {
            return max;
        } else {
            return min;
        }
    } else {
        return v;
    }
}
