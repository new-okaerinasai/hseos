#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char prev = '\n';
    for (int i = 1; i != argc; ++i) {
        int fd;
        if ((fd = open(argv[i], O_RDONLY)) == -1) {
            printf("-1\n");
            continue;
        }
        struct stat statf;
        if (stat(argv[i], &statf) >= 0) {
            if (statf.st_size == 0) {
                printf("0\n");
                continue;
            }
        } else {
            printf("-1\n");
            continue;
        }
        char* mp;
        unsigned long long strings = 0;
        int page_size = getpagesize();
        page_size = (statf.st_size / page_size + 1) * page_size;
        if ((mp = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, 0))) {
            for (int j = 0; j != statf.st_size; prev = mp[j], ++j) {
                if (mp[j] == '\n') {
                    strings += 1;
                }
            }
            if (prev != '\n') {
                strings += 1;
            }
        } else {
            printf("-1\n");
            continue;
        }
        printf("%llu\n", strings);
    }
}