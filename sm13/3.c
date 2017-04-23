#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

struct FileContent read_file(int fd) {
    struct FileContent result;
    result.size = 0;
    result.data = NULL;
    unsigned char buf[4096];
    int success = -1;
    while (success != 0) {
        success = read(fd, buf, sizeof(buf));
        if (success < 0) {
            if (result.data) {
                free(result.data);
            }
            result.size = -1;
            result.data = NULL;
            return result;
        }
        result.size += success;
        char* tmp = realloc(result.data, result.size);
        if (tmp) {
            result.data = tmp;
        } else {
            if (result.data) {
                free(result.data);
            }
            result.size = -1;
            result.data = NULL;
            return result;
        }
        memcpy(result.data + result.size - success, buf, success);
    }
    char* tmp = realloc(result.data, result.size + 1);
    if (tmp) {
        char a = '\0';
        result.data = tmp;
        memcpy(result.data + result.size, &a, 1);
    } else {
        if (result.data) {
            free(result.data);
        }
        result.size = -1;
        result.data = NULL;
        return result;
    }
    return result;
}
