#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

int mystrspccmp(const char* str1, const char* str2) {    
    const char* tmp1 = str1;
    const char* tmp2 = str2;
    while (*tmp1 != '\0' && *tmp2 != '\0') {
        if (isspace(*tmp1) && isspace(*tmp2)) {
            ++tmp1;
            ++tmp2;
        } else if (isspace(*tmp1) && !isspace(*tmp2)) {
            ++tmp1;
        } else if (!isspace(*tmp1) && isspace(*tmp2)) {
            ++tmp2;
        } else {
            if (*(unsigned char *) tmp1 < *(unsigned char *) tmp2) {
                return -1;
            }
            else if (*(unsigned char *) tmp2 < *(unsigned char *) tmp1) {
                return 1;
            }
            ++tmp1;
            ++tmp2;
        }
    }
    while (isspace(*tmp1)) {
        ++tmp1;
    }
    while (isspace(*tmp2)) {
        ++tmp2;
    }
    return *(unsigned char *) tmp1 - *(unsigned char*) tmp2;
}
