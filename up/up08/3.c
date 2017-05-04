#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

void prepare(char* what) {
    char incl[] = "#include <math.h> \n#include <stdio.h>\n";
    char head[] = "double func(double x) {\n";
    char main_p[] = "double result = (";
    char end[] = "); return result; }";
    int fd = open("lmao.c", O_CREAT | O_TRUNC| O_RDWR, 0777);
    write(fd, incl, strlen(incl));
    write(fd, head, strlen(head));
    write(fd, main_p, strlen(main_p));
    write(fd, what, strlen(what));
    write(fd, end, strlen(end));
    close(fd);
    execlp("gcc", "gcc", "-DPIC", "-fPIC", "-shared", "lmao.c", "-o", "lmao.so", NULL);
    _exit(0);
}

int main(int argc, char* argv[]) {
    if (!fork()) { prepare(argv[4]); }
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