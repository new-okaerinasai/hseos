#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int mysys(const char* str) {
    int pid = fork();
    int status;
    if (!pid) {
        execlp("/bin/sh", "/bin/sh", "-c", str, NULL);
    } else if (pid == -1) {
        return 0;
    }
    wait(&status);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    return !((mysys(argv[1]) || mysys(argv[2])) && mysys(argv[3]));
}
