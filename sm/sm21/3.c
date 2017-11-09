#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/eventfd.h>

enum { MAX_LEN = 4096 };

char* add(char* s, int k) {
    int l = strlen(s);
    char r = 1;
    for (int i = 0; i != l; ++i) {
        s[i] += r;
        if (s[i] - '0' == k) {
            s[i] = '0';
            r = 1;
        } else {
            r = 0;
        }
    }
    if (r == 1) {
        s[l] = '1';
        s[l + 1] = '\0';
    }
    return s;
}

int n, k;

int main(int argc, char* argv[]) {
    int* now;
    void* data = mmap(NULL, MAX_LEN + sizeof(*now), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, 0, 0);
    now = (int*)data;
    char* mp = (char*)(data + sizeof(*now));
    strcpy(mp, argv[3]);
    k = atoi(argv[2]);
    n = atoi(argv[1]);
    *now = 1;
    int efd1 = eventfd(0, EFD_SEMAPHORE);
    int efd2 = eventfd(0, EFD_SEMAPHORE);
    if (n == 0) {
        printf("Done\n");
        exit(0);
    }
    if (!fork()) {
        uint64_t a = 1;
        printf("1 %s\n", mp); fflush(stdout);
        ++(*now);
        add(mp, k);
        write(efd2, &a, sizeof(a));
        while (*now < n) {
            read(efd1, &a, sizeof(a));
            printf("1 %s\n", mp); fflush(stdout);
            mp = add(mp, k);
            ++(*now);
            write(efd2, &a, sizeof(a));
        }
        exit(0);
    } else if (!fork()) {
        uint64_t a = 1;
        while (*now < n) {
            read(efd2, &a, sizeof(a));
            printf("2 %s\n", mp); fflush(stdout);
            mp = add(mp, k);
            ++(*now);
            write(efd1, &a, sizeof(a));
        }
        exit(0);
    }
    while(wait(NULL) > 0) { }
    printf("Done\n");
}