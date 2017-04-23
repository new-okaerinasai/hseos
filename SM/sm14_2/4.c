#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>

char* concat(char* str1, char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char slash[] = "/";
    char* ret = malloc(len1 + len2 + 2);
    if (ret) {
        memcpy(ret, str1, len1);
        memcpy(ret + len1, slash, 1);
        memcpy(ret + len1 + 1, str2, len2 + 1);
    }
    return ret;
}

int main(int argc, char* argv[]) {
    DIR* home = opendir(argv[1]);
    uint64_t sum = 0;
    struct dirent* di;
    struct stat statbuf;
    uid_t user = getuid();
    while((di = readdir(home)) != NULL) {
        char* fullpath = concat(argv[1], di->d_name);
        if (stat(fullpath, &statbuf) >= 0) {
            if (S_ISREG(statbuf.st_mode) && statbuf.st_uid == user && isupper(di->d_name[0])) {
                sum += statbuf.st_size;
            }
        }
        free(fullpath);
    }
    closedir(home);
    printf("%llu\n", sum);
}
