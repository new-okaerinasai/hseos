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
#include <math.h>

int main(int argc, char* argv[]) {
    char* path = argv[1];
    int cols = atoi(argv[2]);
    int rows = atoi(argv[3]);
    int fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0600);
    //double** data = malloc(rows*cols*sizeof(double));
    double** data = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    for (int i = 0; i != rows; ++i) {
        for (int j = 0; j != cols; ++j) {
            data[i][j] = 2*sin(i) + 4*cos(j/2);
        }
    }
}
