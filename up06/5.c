#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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
    uint64_t max_size = strtoll(argv[2], NULL, 10);
    uint64_t max = 0;
    DIR* home = opendir(argv[1]);
    struct stat statf;
    uint64_t cumul = 0;
    int do_we_print = 0;
    char* max_name = "\0";
    struct dirent* di;
    while ((di = readdir(home)) != NULL) {
        char* path = concat(argv[1], di->d_name);
        if (lstat(path, &statf) < 0) {
            exit(1);
        }
        if (statf.st_size > max && S_ISREG(statf.st_mode)) {
            max = statf.st_size;
            max_name = di->d_name;
        }
        if (statf.st_size == max && strcmp(di->d_name, max_name) < 0 && S_ISREG(statf.st_mode)) {
            max_name = di->d_name;
        }
        if (S_ISREG(statf.st_mode)) {
            cumul += statf.st_size;
        }
        if (cumul > max_size) {
            do_we_print = 1;
        }
        free(path);
    }
    closedir(home);
    if (do_we_print) {
        printf("%s\n", max_name);
    }
}

