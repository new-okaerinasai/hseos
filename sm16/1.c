#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (!pid) {
        int pid2 = fork();
        if (!pid2) {
            printf("3 ");
            exit(0);
        }
        wait(NULL);
        printf("2 ");
        exit(0);
    }
    wait(NULL);
    printf("1\n");
}
