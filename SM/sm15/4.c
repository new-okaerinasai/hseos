#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <stdlib.h>


char* reverse_str(char* input, int left, int right) {
    char tmp;
    while (left < right) {
        tmp = input[left];
        input[left] = input[right];
        input[right] = tmp;
        ++left;
        --right;
    }
    return input;
}

char* reverse_all(char* input, int size) {
    int left = 0;
    int right = size - 1;
    if (input[size - 1] == '\n') {
        --right;
    }

    if (right > 0) {
        input = reverse_str(input, 0, right);
        for (int right = 0; right <= size; ++right) {
            if (right == size || input[right] == '\n') {
                input = reverse_str(input, left, right - 1);
                left = right + 1;
            }
        }
    }
    return input;
}

int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_APPEND);
    if (fd < 0) {
        exit(1);
    }
    struct stat statf;
    fstat(fd, &statf);
    int page_size = getpagesize();
    page_size = (statf.st_size / page_size + 1) * page_size;
    if (statf.st_size == 0) {
        exit(0);
    }
    char* mp = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        _exit(1);
    }
    mp = reverse_all(mp, statf.st_size);
    char n = '\n';
    if (mp[statf.st_size - 1] != '\n') {
        assert(write(fd, &n, 1));
    }
    close(fd);
}
