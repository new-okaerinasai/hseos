#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* concat(char* file1, char* cmd2, char* cmd3, char* cmd4) {
    size_t len1 = strlen(file1);
    size_t len2 = strlen(cmd2);
    size_t len3 = strlen(cmd3);
    size_t len4 = strlen(cmd4);
    const char first[] = " | (";
    const char second[] = " || ";
    const char third[] = " ) > ";
    size_t f = strlen(first);
    size_t s = strlen(second);
    size_t t = strlen(third);
    char* ret = malloc(len1 + len2 + 20);
    if (ret) {
        memcpy(ret, cmd2, len2);
        memcpy(ret + len2, first, sizeof(first) - 1);
        memcpy(ret + len2 + f, cmd3, len3);
        memcpy(ret + len3 + len2 + f, second, s);
        memcpy(ret + len3 + len2 + f + s, cmd4, len4);
        memcpy(ret + len3 + len2 + len4 + f + s, third, t);
        memcpy(ret + len3 + len2 + len4 + f + s + t, file1, len1 + 1);
    }
    return ret;
}

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

int main(int argc, char* argv[]) {
    char* lmao = concat(argv[1], argv[2], argv[3], argv[4]);
    printf("%s\n", lmao);
    system(lmao);
    free(lmao);
}
