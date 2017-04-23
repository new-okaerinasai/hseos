#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void seek(int fd, int ind) {
    if (ind == 0) {
        return;
    }

    struct Node result;
    off_t seek_success = lseek(fd, sizeof(struct Node)*ind, SEEK_SET);
    if (seek_success < 0) {
        exit(1);
    }
    int success = read(fd, &result, sizeof(struct Node));
    if (success < sizeof(struct Node)) {
        exit(1);
    }

    int32_t right = result.right_idx;
    int32_t left = result.left_idx;
    int32_t key = result.key;

    seek(fd, right);
    
    printf("%"PRId32"\n", key);
    
    seek(fd, left);
}

int main(int argc, char* argv[]) {
    char* name = argv[1];
    int fd = open(name, O_RDONLY);
    struct Node result;

    int success = read(fd, &result, sizeof(struct Node));
    if (success < sizeof(struct Node)) {
        exit(0);
    }

    int32_t right = result.right_idx;
    int32_t left = result.left_idx;
    int32_t key = result.key;

    seek(fd, right);
    
    printf("%"PRId32"\n", key);
    
    seek(fd, left);
}
