#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void invoke(int c, int n) {
    fflush(stdout);
    if (c == 0) {
        if (c != n) {
            printf("%d ", c + 1);
        } else {
            printf("%d\n", c + 1);
        } 
        exit(0);
    }
    if (!fork()) {
        invoke(c - 1, n);
        exit(0);
    }
    wait(NULL);
    if (c != n) {
        printf("%d ", c + 1);
    } else {
        printf("%d\n", c + 1);
    }
}

int main() {
    int c;
    scanf("%d", &c);
    invoke(c - 1, c - 1);
}

