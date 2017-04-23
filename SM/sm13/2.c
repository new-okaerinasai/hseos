#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(int in_fd, int out_fd) {
    char buf[4096];
    int read_actually = -1;
    while(read_actually != 0) {
        read_actually = read(in_fd, buf, sizeof(buf));
        if (read_actually == -1)
            break;
        int t = 0;
        while (read_actually != t) {
            int write_size = write(out_fd, buf + t, read_actually - t);
            t += write_size;
        }
    }
}
