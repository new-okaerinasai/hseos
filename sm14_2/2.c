#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    unsigned long long sum = 0;
    struct stat st;
    for (int i = 1; i != argc; ++i) {
        if (lstat(argv[i], &st) != -1) {
            if (st.st_nlink == 1 && S_ISREG(st.st_mode)) {
                sum += st.st_size;
            }
        }
    }
    printf("%llu\n", sum);
}