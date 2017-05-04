#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char host[1000], service[1000];
    while ((scanf("%s[^ ]", host) != -1) && (scanf("%s[^\n]", service) != -1)) {
        struct addrinfo hints = {};
        struct addrinfo* result;
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        int err = getaddrinfo(host, service, &hints, &result);
        if (err) {
            printf("%s\n", gai_strerror(err));
            continue;
        }
        struct addrinfo* now = result;
        struct sockaddr* min = now->ai_addr;
        unsigned long s = (((struct sockaddr_in*)min)->sin_addr).s_addr;
        s = ntohl(s);
        struct sockaddr_in* final = (struct sockaddr_in*)result->ai_addr;
        while (now != NULL) {
            struct sockaddr* tmp = now->ai_addr;
            unsigned long s2 = (((struct sockaddr_in*)tmp)->sin_addr).s_addr;
            s2 = ntohl(s2);
            if (s2 < s) {
                final = (struct sockaddr_in*)now->ai_addr;
                s = s2;
            }
            now = now->ai_next;
        }
        printf("%s:%hu\n", inet_ntoa(final->sin_addr), ntohs(final->sin_port));
    }
}