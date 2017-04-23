#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t n = 0;
    int32_t begin = 0, end = 0;
    int32_t previous = 0, current = 0;
    uint32_t max = 0;
    if (scanf("%d", &begin) != -1) { // Обработать первый элемент, если он есть
        current = begin;
        while (scanf("%d", &n) != -1) {
            previous = current;
            current = n;
            if (current < previous) {
                end = previous;
                if ((uint32_t)end - (uint32_t)begin > max) {
                    max = end - begin;
                }
                begin = current;
            }
        }
    }    
    if (current - begin > max) { // Обработать конец последовательности отдельно
        max = current - begin;
    }
    printf("%u\n", max);
}
1