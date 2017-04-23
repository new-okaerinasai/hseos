#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void kill_all(int* pids, int count) {
    for (int i = 0; i != count; ++i) {
        kill(pids[i], SIGKILL);
    }
    _exit(1);
}

int main(int argc, char* argv[]) {
    int fds[2];
    int oldfd = 0;
    int pids[argc];
    int count = 0;
    if (argc == 1) {
        _exit(0);
    }
    if (argc == 2) {
        execlp(argv[1], argv[1], NULL);
        _exit(0);
    }
    for (int i = 1; i != argc; ++i) {
        char* cmd = argv[i];
        int success = pipe(fds);
        if (success == -1) {
            kill_all(pids, count);
        }
        int pid;
        if (i == 1) {
            pid = fork();
            if (pid == -1) {
                kill_all(pids, count);
            }
            if (!pid) {
                dup2(fds[1], 1);
                pids[i] = pid;
                close(fds[0]); close(fds[1]);
                execlp(cmd, cmd, NULL);
            }
            ++count;
            close(fds[1]);
        } else if (i == argc - 1) {
            pid = fork();
            if (pid == -1) {
                kill_all(pids, count);
            }
            if (!pid) {
                dup2(oldfd, 0);
                pids[i] = pid;
                close(fds[1]); close(fds[0]);
                close(oldfd);
                execlp(cmd, cmd, NULL);
            }
            ++count;
            close(oldfd); close(fds[1]);
            close(fds[0]);
        } else {
            pid = fork();
            if (pid == -1) {
                kill_all(pids, count);
            }
            if (!pid) {
                dup2(oldfd, 0);
                pids[i] = pid;
                dup2(fds[1], 1);
                close(fds[1]); close(oldfd);
                execlp(cmd, cmd, NULL);
            }
            ++count;
            close(oldfd); close(fds[1]);
        }
        oldfd = fds[0];
    }
    while (wait(NULL) > 0) { }
}
