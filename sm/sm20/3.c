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

int main(int argc, char* argv[]) {
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        exit(0);
    }

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;
    sa.sin_port = htons(atoi(argv[1]));

    if (bind(fd, (void*) &sa, sizeof(sa)) < 0) {
        exit(0);
    }

    if (listen(fd, 5) < 0) {
        exit(0);
    }
    
    int sum = 0;
    int now = -1;
    
    while (now != 0) {
        struct sockaddr_in ss;
        socklen_t sz = sizeof(ss);
        int afd = accept(fd, (void*) &ss, (unsigned*)&sz);
        if (afd < 0) {
            exit(0);
        }
        
        read(afd, &now, sizeof(now));
        now = ntohl(now);
        sum += now;
        close(afd);
    }
    close(fd);
    printf("%d\n", sum); fflush(stdout);
}
