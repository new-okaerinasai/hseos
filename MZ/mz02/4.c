#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

int64_t extract(int64_t value, int bit, int length) {
    value = (uint64_t)value;
    for (int i = 0; i != (length + bit - 1); ++i) {
        uint64_t max = (1 << 1) + 1; 
    }

    value = value >> (64 - (length + bit));

}

int main() {

}