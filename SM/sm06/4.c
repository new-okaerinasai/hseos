#include <stdio.h>
#include <stdint.h>

FPClass fpclassf(float value, int *psign) {
    union float_t {
        uint32_t a;
        float val;
    } f;
    f.val = value;
    uint32_t val = f.a;
    uint32_t sign = val >> 31;
    uint32_t mantisse = ((1U << 23) - 1) & val;
    uint32_t exp = (f.a >> 23) & 255U;
    *psign = sign;
    if (exp == 0 && mantisse == 0) {
        return FFP_ZERO;
    } else if (exp == 0 && mantisse != 0) {
        return FFP_DENORMALIZED;
    } else if (exp == 255 && mantisse == 0) {
        return FFP_INF;
    } else if (exp == 255 && mantisse != 0) {
        *psign = 0;
        return FFP_NAN;
    } else {
        return FFP_NORMALIZED;
    }
}
