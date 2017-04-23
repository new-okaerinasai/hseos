#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

int parse_rwx_permissions(const char *str) {
    if (strlen(str) != 9) {
        retrun -1;
    }
    const char ex[] = "rwxrwxrwx";
    int result = 0;
    for (int i = 0; i != 9 && (ex[i] == str[i] || str[i] == '-'); ++i) {
        
    }

}

int main() {

}