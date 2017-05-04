#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    struct addrinfo hints = {};
    struct addrinfo* result;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int err = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (err) {
        _exit(0);
    }
    struct addrinfo* where = result;
    
    int fd = socket(where->ai_family, where->ai_socktype, where->ai_protocol);
    int fd2 = dup(fd);
    FILE* out = fdopen(fd, "a+");
    FILE* in = fdopen(fd2, "a+");
    if (connect(fd, where->ai_addr, where->ai_addrlen) < 0) {
        _exit(0);
    }
    err = fprintf(out, "%s\n", argv[3]); fflush(out);

    if (err <= 0) {
        _exit(0);
    } else {
        int k;
        if (fscanf(in, "%d", &k) <= 0) {
            _exit(0);
        } else {
            for (int i = 0; i <= k; ++i) {
                err = fprintf(out, "%d\n", i); fflush(out);
                if (err <= 0) {
                    _exit(0);
                }
            }
            uint64_t result = 0;
            err = fscanf(in, "%lu", &result);
            if (err <= 0) {
                _exit(0);
            }
            printf("%lu\n", result); fflush(stdout);
        }
    }
}
