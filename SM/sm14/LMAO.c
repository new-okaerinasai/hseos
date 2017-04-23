#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main() {
    time_t clock; 
    time(&clock);
    int c;
    while (scanf("%d", &c) != -1) {
        if (__builtin_mul_overflow(c, 86400, &c)) {
            printf("OVERFLOW\n");
            continue;
        }
        time_t new_clock;
        if (__builtin_add_overflow(clock, c, &new_clock)) {
            printf("OVERFLOW\n");
            continue;
        }
        struct tm* now = localtime(&new_clock);
        printf("%04d-%02d-%02d\n", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
    }
}
