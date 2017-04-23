#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    size_t count = 0;
    long long sum_int = 0;
    size_t sum_length = 0;
    double avg = 0, sum_double = 0;
    for (int i = 1; i < argc; ++i) {
        char* str = argv[i];
        if (*str == 'i') {
            ++str;
            sum_int += strtoll(str, NULL, 10);
        } else if (*str == 'd') {
            ++str;
            sum_double += strtod(str, NULL);
            ++count;
        } else {
            sum_length += strlen(str);
        }
    }
    if (count != 0) {
        avg = sum_double / count;
    } else {
        avg = 0;
    }
    printf("%.10g\n%lld\n%lu\n", avg, sum_int, sum_length);
}
