
#include <stdio.h>
#include <stdint.h>

int main() {
    int n, w;
    if (scanf("%d%d", &n, &w) != -1) {
        int32_t max = 1;
        max = max << n;
        int32_t sign = -(max / 2);
        for (int i = 0; i < max; ++i) {
            if (i < max / 2) {
                printf("|%*u|%*x|%*d|\n", w, i, w, i, w, i);
            } else {
                printf("|%*u|%*x|%*d|\n", w, i, w, i, w, sign);
                ++sign;
            }
        }
    }
}
