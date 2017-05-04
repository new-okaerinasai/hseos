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
        _exit(0);
    }

    int val = 1;
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
    
    int sum = 0;
    int now = -1;
    
}
