#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (!fork()) {
        int fd_read = open(argv[2], O_RDONLY);
        int fd_write = open(argv[3], O_CREAT|O_TRUNC|O_WRONLY, 0666);
        dup2(fd_write, 1); close(fd_write);
        dup2(fd_read, 0); close(fd_read);
        execlp(argv[1], argv[1],  NULL);
        _exit(1);
    }
    wait(NULL);
    return 0;
}

