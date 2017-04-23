#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    double a = strtod(argv[1], NULL);
    for (int i = 1; i < argc / 2; ++i) {
        void* handle = dlopen(argv[2 * i], RTLD_LAZY);
        void* func = dlsym(handle, argv[2 * i + 1]);
        if (func != NULL && handle != NULL) {
            a = ((double (*)(double))func)(a);
        }
    }
    printf("%.10g\n", a);
}
