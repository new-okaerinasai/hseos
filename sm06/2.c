#include <stdio.h>
#include <stdint.h>

int main() {
    union {
        float a;
        uint32_t n;
    } f;
    while (scanf("%f", &f.a) != -1) {
        uint32_t sign = (f.n >> 31);
        uint32_t exp = (f.n >> 23) & 255;
        uint32_t mantisse = ((1U << 23) - 1) & f.n;
        printf("%u %u %x\n", sign, exp, mantisse);
    }
}
