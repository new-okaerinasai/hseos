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
    val >>= (length + 1);
    length = 32 - length;
    --length;
    unsigned exp = (length + 15) << 0;
    printf("%d\n", length);
    if (length > 10) {
        unsigned bia = 1U << (length - 10);
        val += bia; // округлили
        val >>= (length - 10);
    }
    printf("%d\n", val);
    val += exp;
    *hf += val;
}

int main() {
    unsigned short a;
    int b;
    scanf("%d", &b);
    to_half_float(b, &a);
    printf("%d -> %x\n", b, a);
}
