#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

uint16_t reverse(uint16_t a) {
    uint16_t res = 0;
    for (int i = 0; i != 15; ++i) {
        uint16_t b = a & 1;
        res += b;
        a >>= 1;
        res <<= 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    char* name = argv[1];
    int d = open(name, O_RDONLY);
    uint16_t a;
    uint16_t max = 0;
    while(read(d, &a, 2) > 0) {
        uint16_t little = a & 0x00FF;
        uint16_t big = a & 0xFF00;
        big >>= 8;
        little <<= 8;
        a = big + little;
        if (a % 2) {
            if (a > max) {
                max = a;
            }
        }
    }
    if (max != 0) {
        printf("%u\n", max);
    }
}
