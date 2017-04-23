#include <stdio.h>
#include <ctype.h>

int main() {
    int max = 0;
    int max_2 = 0;
    int number = 0;
    while (scanf("%d", &number) == 1) {
        if (number > max) {
            max_2 = max;
            max = number;
        }
        else if (number > max_2) {
            max_2 = number;
        } 
    }
    int p = max * max_2;
    printf("%d\n", p);
}
