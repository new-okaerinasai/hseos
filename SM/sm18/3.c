#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char* cmd1 = argv[1];
    char* cmd2 = argv[2];
    char* cmd3 = argv[3];
    int fds[2];
    pipe(fds);
    if (!fork()) {
        close(fds[0]);
        if (!fork()) {
            dup2(fds[1], 1);
            close(fds[1]);
            close(fds[0]);
            execlp(cmd1, cmd1, NULL);
            _exit(0);
        }
        wait(NULL);
        if (!fork()) {
            dup2(fds[1], 1);
            close(fds[1]);
            close(fds[0]);
            execlp(cmd2, cmd2, NULL);
            _exit(0);
        }
        close(fds[1]);
        wait(NULL);
        _exit(0);
    } else if (!fork()) {
        dup2(fds[0], 0);
        int fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd, 1);
        close(fds[1]); close(fds[0]); close(fd);
        execlp(cmd3, cmd3, NULL);
        _exit(0);
    }
    close(fds[1]);
    close(fds[0]);
    wait(NULL); wait(NULL);
}
