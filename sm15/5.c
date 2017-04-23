#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Arguments 
{
    unsigned char args[64];
};

int main(int argc, char* argv[]) {
    void *handle;
    handle = dlopen(argv[1], RTLD_LAZY);
    char* name = argv[2];
    char* signature = argv[3];
    void *func = dlsym(handle, name);
    struct Arguments params;
    int offset = 0;
    for (int i = 4; i != argc; ++i) {
        if (signature[i - 3] == 'i') {
            int tmp = atoi(argv[i]);
            memcpy(params.args + offset, &tmp, 4);
            offset += 4;
        } else if (signature[i - 3] == 'd') {
            double tmp = strtod(argv[i], NULL);
            memcpy(params.args + offset, &tmp, 8);
            offset += 8;
        } else if (signature[i - 3] == 's') {
            memcpy(params.args + offset, &argv[i], 4);
            offset += 4;
        } else {
            fprintf(stderr, "3RROR");
        }
    }
    if (signature[0] == 'v') {
        ((void (*)(struct Arguments))func)(params);
    } else if (signature[0] == 'i') {
        int result = ((int (*)(struct Arguments))func)(params);
        printf("%d\n", result);
    } else if (signature[0] == 'd') {
        double result = ((double (*)(struct Arguments))func)(params);
        printf("%.10g\n", result);
    } else if (signature[0] == 's') {
        char* result = ((char* (*)(struct Arguments))func)(params);
        printf("%s\n", result);
    } else {
        fprintf(stderr, "3RROR");
    }
}
