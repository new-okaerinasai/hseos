#include <stdio.h>
#include <stdint.h>

int myccompare(char c1, char c2) {
    if (c1 == c2) {
        return 1;
    }
    if (c1 == '/' && c2 == '\0') {
        return 1;
    }
    if (c1 == '\0' && c2 == '/') {
        return 1;
    }
    return 0;
}

int mystrcmp(const char* str1, const char* str2) {    
    const char* tmp1 = str1;
    const char* tmp2 = str2;
    for ( ; myccompare(*tmp1, *tmp2) ; ++tmp1, ++tmp2) {
        if (*tmp1 == '/' || *tmp1 == '\0') {
            return 1;
        }
    }
    return 0;
}


void common_dir(const char *d1, const char *d2, char *out) {
    int length = 0;
    for (; *d1 == *d2; ++d1, ++d2) {
        if (mystrcmp(d1, d2)) {
            *out = *d1;
            ++out;
            ++length;
        }
        if (!(*d2))
            break;
    }
    --out;
    if (*out == '/' && length != 1) {
        *out = '\0';
    } else {
        ++out;
        *out = '\0';
    }
}
