#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (!fork()) {
        int fd = open("lmao.c", O_CREAT | O_TRUNC| O_WRONLY, 0666);
        FILE* pre = fdopen(fd, "w");
        fprintf(pre, "#include <math.h> \n#include <stdio.h>\n");
        fprintf(pre, "double func(double x) {\n");
        fprintf(pre, "double result = (");
        fprintf(pre, "%s", argv[4]);
        fprintf(pre, "); return result; }");
        fclose(pre);
        close(fd);
        execlp("gcc", "gcc", "-DPIC", "-fPIC", "-shared", "lmao.c", "-o", "lmao.so", NULL);
        _exit(0);
    }
    wait(NULL);
    void* handler = dlopen("./lmao.so", RTLD_LAZY);
    void* func = dlsym(handler, "func");
    int n = atoi(argv[3]);
    double left = strtod(argv[1], NULL);
    double right = strtod(argv[2], NULL);
    double dx = (right - left) / n;
    double result = 0;
    for (int i = 0; i != n; ++i) {
        double x = left + i * dx;
        double s = ((double (*)(double))func)(x) * dx;
        result += s;
    }
    printf("%.10g\n", result);
}