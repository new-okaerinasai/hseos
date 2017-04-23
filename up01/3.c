#include <stdint.h>

uint64_t addmod(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t v;
    if ((v = a + b) < a) {
        uint64_t max = ~(uint64_t)0;
        return ((v + 1) % c + max % c) % c;
    } else {
        return (a + b) % c;
    }
    return a + b;
}
