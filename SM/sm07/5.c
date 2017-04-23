#include <wctype.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>

int main() {
    wchar_t c;
    setlocale(LC_ALL, "en_US.utf8");
    unsigned long long length = 0;
    wchar_t* word = calloc(12, sizeof(*word));
    wchar_t* tmp = word;
    while ((c = getwchar()) != WEOF) {
        if ( ) {
            if (*tmp == L'\0') {
                
            }
            *tmp = 
        } else {

        }
    }
}
