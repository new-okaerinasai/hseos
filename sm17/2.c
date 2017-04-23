#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int mysys(const char* str) {
    int pid = fork();
    int status;
    if (!pid) {
        execlp("/bin/sh", "/bin/sh", "-c", str, NULL);
    } else if (pid == -1) {
        return -1;
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 128;
    }
    return -1;
}

