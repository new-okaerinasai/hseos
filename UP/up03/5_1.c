#include <stdio.h>

unsigned new_abs(int value) {
    if (value < 0) {
        return -(unsigned)value;
    } else {
        return (unsigned)value;
    }
}

void to_half_float(int value, unsigned short* hf) {
    if (value < 0) {
        *hf = (1U << 15);
    } else {
        *hf = 0;
    }
    unsigned int val = new_abs(value);
    unsigned int sign = 1U << 31;
    int length = 0;
    while (!(sign & val) && (length < 32)) {
        ++length;
        val <<= 1;
    }
    val <<= 1;
    unsigned old_val = val;
    length = 32 - (length + 1);
    val += (1U << 21); // округлили
    if (val < old_val) {
        ++length;
    }
    val >>= 22;
    unsigned exp = (length + 15) << 10;
    if (value == 0) {
        exp = 0;
    }
    if (length + 15 < 31) {
        val += exp;
    } else {
        val = 0;
        val += exp;
    }
    *hf += val;
}
