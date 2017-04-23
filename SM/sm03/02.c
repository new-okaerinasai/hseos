#include <stdio.h>
#include <ctype.h>

int main() {
    int a, b, n;
    int kek = scanf("%d %d %d", &a, &b, &n) == 1;
    printf("%d%d*n", a, b);
    printf("%d", kek);
}