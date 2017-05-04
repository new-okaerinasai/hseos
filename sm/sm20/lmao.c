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
#include <fcntl.h>

int main() {
	int fd = open("2.c", O_RDONLY);
	FILE* kek = fdopen(fd, "r");
	char buf[1000];
	printf("%d\n", fscanf(kek, "%s", buf));
	printf("%s\n", buf);
	close(fd);
	printf("%d\n", fscanf(kek, "%s", buf));
	printf("%s\n", buf);
}