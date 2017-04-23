#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

struct Data
{
    int16_t x; // 2 байта,
    int64_t y; // 8 байт
};

int main(int argc, char* argv[]) {
    struct stat st;
    int a = atoi(argv[2]);

    int fd = open(argv[1], O_RDWR);

    ssize_t begin = 0, end = 0;

    stat(argv[1], &st);
    ssize_t sz = st.st_size;

    if (sz % (sizeof(uint64_t) + sizeof(uint16_t)) != 0) {
        exit(1);
    }

    lseek(fd, 0, SEEK_SET);
    
    while (sz > 0) {
        struct Data tmp1, tmp2;

        lseek(fd, (sizeof(uint64_t) + sizeof(uint16_t)) * begin, SEEK_SET);
        if (read(fd, &tmp1.x, sizeof(uint16_t)) < sizeof(uint16_t)) {
            exit(1);
        }
        if (read(fd, &tmp1.y, sizeof(uint64_t)) < sizeof(uint64_t)) {
            exit(1);
        }

        lseek(fd, -(sizeof(uint64_t) + sizeof(uint16_t)) * (end + 1), SEEK_END);
        if (read(fd, &tmp2.x, sizeof(uint16_t)) < sizeof(uint16_t)) {
            exit(1);
        }
        if (read(fd, &tmp2.y, sizeof(uint64_t)) < sizeof(uint64_t)) {
            exit(1);
        }

        tmp1.y += tmp1.x * a;
        tmp2.y += tmp2.x * a;

        lseek(fd, -(sizeof(uint64_t) + sizeof(uint16_t)) * (end + 1), SEEK_END);
        if (write(fd, &tmp1.x, sizeof(uint16_t)) < sizeof(uint16_t)) {
            exit(1);
        }
        if (write(fd, &tmp1.y, sizeof(uint64_t)) < sizeof(uint64_t)) {
            exit(1);
        }

        lseek(fd, (sizeof(uint64_t) + sizeof(uint16_t)) * begin, SEEK_SET);
        if (write(fd, &tmp2.x, sizeof(uint16_t)) < sizeof(uint16_t)) {
            exit(1);
        }
        if (write(fd, &tmp2.y, sizeof(uint64_t)) < sizeof(uint64_t)) {
            exit(1);
        }

        ++end;
        ++begin;
        sz -= 2 * (sizeof(uint64_t) + sizeof(uint16_t));
    }
}
