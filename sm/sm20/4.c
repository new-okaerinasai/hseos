#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <sys/mman.h>

void handler(int s) {
    fcloseall();
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handler);

    int ppid = getpid();

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        _exit(0);
    }

    int val = 1;
    int err;

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(atoi(argv[1]));

    if (bind(fd, (void*) &sa, sizeof(sa)) < 0) {
        _exit(0);
    }

    if (listen(fd, 5) < 0) {
        _exit(0);
    }

    int* serial = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, 0, 0);
    *serial = 1;

    while (1) {
        struct sockaddr_in ss;
        socklen_t sz = sizeof(ss);
        int afd = accept(fd, (void*) &ss, &sz);
        if (afd < 0) {
            _exit(0);
        }

        int pid;
        if (!(pid = fork())) {
            FILE* in = fdopen(afd, "w+");
            int nfd = dup(afd);
            FILE* out = fdopen(nfd, "w+");
            
            err = fprintf(out, "%s\r\n", argv[2]); fflush(out);
            if (err <= 0 || should) {
                _exit(0);
            }

            err = fprintf(out, "%d\r\n", *serial); fflush(out);
            if (err <= 0 || should) {
                _exit(0);
            }

            ++(*serial);
            int max;

            err = fscanf(in, "%d", &max);
            if (err <= 0) {
                _exit(0);
            }
            
            err = fprintf(out, "%d\r\n", max); fflush(out);
            if (err <= 0) {
                _exit(0);
            }

            int num = 0, result = 0;
            int ovf = 0;

            while (num <= max && !ovf) {
                err = fscanf(in, "%d", &num);
                if (err <= 0) {
                    _exit(0);
                }
                ovf = __builtin_add_overflow(num, *serial, &result);
                if (!ovf) {
                    err = fprintf(out, "%d\r\n", result); fflush(out);
                    if (err <= 0) {
                        _exit(0);
                    }
                } else {
                    err = fprintf(out, "%d\r\n", -1); fflush(out);
                    if (err <= 0) {
                        _exit(0);
                    }
                }
            }
            close(afd);
            _exit(0);
        }
    }
}
