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

int main(int argc, char* argv[]) {
    uint64_t max_size = strtoll(argv[2], NULL, 10);
    uint64_t max = 0;
    DIR* home = opendir(argv[1]);
    struct stat statf;
    uint64_t cumul = 0;
    struct dirent **namelist;
    int fd = dirfd(home);
    int do_we_print = 0;
    char* max_name = NULL;
    int n = scandir(argv[1], &namelist, NULL, alphasort);
    for (int i = 0; i != n; ++i) {
        fstatat(fd, namelist[i]->d_name, &statf, AT_SYMLINK_NOFOLLOW);
        if (statf.st_size > max && S_ISREG(statf.st_mode)) {
            max = statf.st_size;
            max_name = namelist[i]->d_name;
        }
        if (S_ISREG(statf.st_mode)) {
            cumul += statf.st_size;
        }
        if (cumul > max_size) {
            do_we_print = 1;
        }
    }
    if (do_we_print) {
        printf("%s\n", max_name);
    }
    while(n--) {
        free(namelist[n]);
    }
}