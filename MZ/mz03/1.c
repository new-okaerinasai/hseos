#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main() {
    wchar_t c;
    setlocale(LC_ALL, "");
    int should_capital = 1;
    while ((c = getwchar()) != WEOF) {
        if (c != L'.' && c != L'!' && c != L'?') {
            if (!iswspace(c)) {
                if (should_capital) {
                    wprintf(L"%lc", towupper(c));
                    should_capital = 0;
                } else {
                    wprintf(L"%lc", c);
                }
            } else {
                wprintf(L"%lc", c);
            }
        } else {
            wprintf(L"%lc", c);
            should_capital = 1;
        }
    }
}
