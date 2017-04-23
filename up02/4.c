#include <stdint.h>

int64_t extract(int64_t value, int bit, int length) {
    uint64_t val = (uint64_t)value;
    val <<= 64 - length - bit;
    int64_t new_val = (int64_t)val;
    new_val >>= 64 - length;
    return new_val;
}
