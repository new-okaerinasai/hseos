#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    int fds[2];
    pipe(fds);
    if (!fork()) {
        dup2(fds[1], 1);
        close(fds[1]);
        close(fds[0]);
        execlp(argv[1], argv[1], NULL);
        _exit(0);
    }
    close(fds[1]);
    if (!fork()) {
        dup2(fds[0], 0);
        close(fds[0]);
        close(fds[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(0);
    }
    close(fds[0]);
    wait(NULL);
    wait(NULL);
}

