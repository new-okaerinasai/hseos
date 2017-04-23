#include <stdio.h>
#include <stdint.h>

int cmpf(const float *p1, const float *p2) {
    union float_tag {
        uint32_t a;
        float t;
    } f1, f2;
    f1.t = *p1;
    f2.t = *p2;
    uint32_t sign1 = (f1.a >> 31), sign2 = (f2.a >> 31);
    uint32_t exp1 = (f1.a >> 23) & 255, exp2 = (f2.a >> 23) & 255;
    uint32_t mantisse1 = ((1U << 23) - 1) & f1.a, mantisse2 = ((1U << 23) - 1) & f2.a;
    if (f1.a == f2.a) {
        return 0;
    } else {
        if (sign1 < sign2) {
            return 1;
        } else if (sign2 < sign1) {
            return -1;
        } else {
            if (!sign1) {
                if (exp1 > exp2) {
                    return 1;
                } else if (exp2 > exp1) {
                    return -1;
                } else {
                    if (mantisse1 > mantisse2) {
                        return 1;
                    } else if (mantisse2 > mantisse1) {
                        return -1;
                    }
                }
            } else {
                if (exp1 < exp2) {
                    return 1;
                } else if (exp2 < exp1) {
                    return -1;
                } else {
                    if (mantisse1 < mantisse2) {
                        return 1;
                    } else if (mantisse2 < mantisse1) {
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}
