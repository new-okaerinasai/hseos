#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int mysystem(const char* str) {
    size_t l = strlen(str);
    char* tmp = malloc(l + 1);
    memcpy(tmp, str, l + 1);
    
    while(isspace(*str)) {
        ++str;
    }
    size_t argc = 0;
    char prev = ' ';
    while (*str != '\0') {
        if (!isspace(*str) && isspace(prev)) {
            ++argc;
        }
        prev = *str;
        ++str;
    }
    if (argc == 0) {
        return -1;
    }
    const char** result = malloc((argc + 1)*sizeof(const char*));
    int i = 0;
    prev = '\0';
    for (int k = 0; k != l; ++k) {
        if (isspace(tmp[k])) {
            tmp[k] = '\0';
        } else {
            if (prev == '\0') {
                result[i] = tmp + k;
                ++i;
            }
        }
        prev = tmp[k];
    }
    result[i] = NULL;
    int status;
    int pid = fork();
    if (!pid) {
        int ret = execvp(result[0], (char* const*)result);
        if (ret == -1) {
            _exit(1);
        }
    } else if (pid == -1) {
        return -1;
    }
    wait(&status);
    free(result);
    free(tmp);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 1024;
    }
    return 0;
}
