#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t n;
    while (scanf("%u", &n) != -1) {
        if (n == 0) {
            printf("%d\n", 1);
        } else {
            uint32_t max = (uint32_t)1 << 31;
            uint32_t num = n;
            uint32_t num1 = n;
            int left = 0, right = 0;
            while (!(num1 & 1)) {
                num1 = num1 >> 1;
                ++right;
            }
            while (!(max & num)) {
                num = num << 1;
                ++left;
            }
            printf("%d\n", 32 - (left + right) <= 24);
        }
    }
}
