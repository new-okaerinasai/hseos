#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int main(int argc, char *argv[])
{
    assert(argc >= 2);
    struct Node array[1000];
    size_t size;
    scanf("%zu", &size);
    for (size_t i = 0; i != size; ++i) {
        scanf("%"SCNd32, &array[i].key);
    }
    for (size_t i = 0; i != size; ++i) {
        array[i].left_idx = 0;
        array[i].right_idx = i + 1;
    }
    array[size - 1].right_idx = 0;
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    write(fd, &array[0], size*sizeof(struct Node));
    
    return 0;
}