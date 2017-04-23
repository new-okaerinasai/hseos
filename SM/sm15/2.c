#include <stdio.h>

int main() {
    unsigned begin, end;
    unsigned long long result = 0;
    while (scanf("%x-%x %*[^\n]", &begin, &end) != -1) {
        result += (end - begin);
    }
    printf("%llu\n", result);
}
