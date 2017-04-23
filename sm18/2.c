#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int fds[2];
    pipe(fds);
    int x;
    long long sum = 0;
    if (!fork()) {
        if (!fork()) {
            int s;
            close(fds[1]);
            while (read(fds[0], &s, sizeof(s))) {
                sum += s;
            }
            close(fds[0]);
            printf("%lld\n", sum); fflush(stdout);
            _exit(0);
        }
        close(fds[0]); close(fds[1]);
        wait(NULL);
        _exit(0);
    }
    close(fds[0]);
    while (scanf("%d", &x) != -1) {
        write(fds[1], &x, sizeof(x));
    }
    close(fds[1]);
    wait(NULL);
}
