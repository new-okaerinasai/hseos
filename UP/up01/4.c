#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main() {
    char c, previous = ' ';
    long long int sum = 0;
    int isbig = 0;
    while((c = getchar_unlocked()) != EOF) {
        if (!isspace(c)) {
            if (c == '1') {
                sum = 3*sum + 1;
            }
            if (c == 'a') {
                sum = 3*sum - 1;
            }
            if (c == '0') {
                sum = 3*sum;
            }
            if (sum > INT_MAX || sum < INT_MIN + 1) {
                isbig = 1; // просто примем, что число "большое"
            }
        }
        else {
            if (!isspace(previous)) {
                if (!isbig) {
                    printf("%lld\n", sum);
                } else {
                    printf("%d\n", INT_MIN);
                }
            sum = 0;
            isbig = 0;
            }
        }
        previous = c;
    }
}
