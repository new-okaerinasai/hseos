#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int mult_by3(int a) {
    return (a << 1) + a;
}

int div_by3 (int a) {
    int k, r;
    int result = 0;
    while(a > 4) {
        k = a >> 2;
        r = a - (k << 2);
        result += k;
        a = k + r;
    }
    if (a > 2) {
        result += 1;
    }
    return result;
}

int check3(int a) {
    int l = div_by3(a);
    l = mult_by3(l);
    return a == l;
}

int parse_rwx_permissions(const char* str) {
    const char example[] = "rwxrwxrwx";
    size_t ten = sizeof(example);
    if (str == NULL) {
        return -1;
    }
    if (strlen(str) != ten - 1) {
        return -1;
    }
    for (int i = 0; i != ten - 1; ++i) {
        if (str[i] != '-' && str[i] != example[i]) {
            return -1;
        }
    }
    int result = 0;
    int tmp = 0;
    for (int i = 0; i < ten - 1; ++i) {
        if (str[i] == example[i]) {
            tmp += 1;
        }
        tmp <<= 1;
        if (check3(i + 1)) {
            tmp >>= 1;
            result = tmp + 2*(result << 2);
            tmp = 0;
        }
    }
    return result;
}
