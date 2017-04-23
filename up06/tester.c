#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    assert(argc >= 2);
    double numbers[100];
    size_t i = 0;
    while (scanf("%lf", &numbers[i++]) != EOF);

    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
    write(fd, &numbers[0], i * sizeof(double));

    return 0;
}
