#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main() {
    wchar_t c;
    setlocale(LC_ALL, "");
    unsigned long long numbers = 0, capitals = 0, lowercase = 0;
    while ((c = getwchar()) != WEOF) {
        if (iswdigit(c)) {
            ++numbers;
        } else if (iswlower(c)) {
            ++lowercase;
        } else if (iswupper(c)) {
            ++capitals;
        }
    }
    printf("%llu\n%llu\n%llu\n", numbers, capitals, lowercase);
}
