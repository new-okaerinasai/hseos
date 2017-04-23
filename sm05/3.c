#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int is32(long n) {
    int32_t num32 = (int32_t)n;
    int8_t num8 = (int8_t)n;
    int16_t num16 = (int16_t)n;
    if (num8 == n) {
        return 1;
    } else if (num16 == n) {
        return 2;
    } else if (num32 == n) {
        return 4;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        errno = 0;
        char* str = argv[i];
        char  *end;
        long number = strtol(str, &end, 10);
        if (*str && !errno && !*end) {
            printf("%d\n", is32(number));
        } else {
            printf("%d\n", -1);
        }
    }
}
