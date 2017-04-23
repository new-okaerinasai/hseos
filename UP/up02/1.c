#include <stdint.h>
#include <stdio.h>

int main() {
    uint32_t result = 0;
    int n;
    uint32_t temp = 0;
    while (scanf("%d", &n) != -1) {
        if (n != -1) {
            temp = temp | (1U << n);
        } else {
            result = result ^ temp;
            temp = 0;
        }
    }
    printf("%x\n", result);
}
