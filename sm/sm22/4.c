#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
enum { MAX_COUNT = 100 };

int n;

int fds[MAX_COUNT][2];

void* thread_fig(void* what) {
    long long k = (long long)what;
    int cm;
    while (read(fds[k][0], &cm, sizeof(cm)) > 0) {
        if (cm == 1) {
            int r;
            int p;
            if (scanf("%d", &r) != -1) {
                printf("%lld %d\n", k, r);
                p = 1;
                r = r % n;
                if (r < 0) {
                    r += n;
                }
                write(fds[r][1], &p, sizeof(p));
            } else {
                p = 0;
                for (int i = 0; i != n; ++i) {
                    write(fds[i][1], &p, sizeof(p));
                }
            }
        } else {
            pthread_exit(NULL);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    n = atoi(argv[1]);
    pthread_t* ids = calloc(n, sizeof(*ids));
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != n; ++i) {
        pipe(fds[i]);
        pthread_create(&ids[i], &attr, thread_fig, (void*)(long long)i);
    }
    int now = 1;
    write(fds[0][1], &now, sizeof(now));
    for (int i = 0; i != n; ++i) {
        pthread_join(ids[i], NULL);
    }
    for (int i = 0; i != n; ++i) {
        close(fds[i][1]); close(fds[i][0]);
    }
    free(ids);
}
