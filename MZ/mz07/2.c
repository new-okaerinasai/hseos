#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

extern char** environ;

int main(int argc, char* argv[]) {
    double a;
    char buf[222];
    scanf("%lg", &a);
    char prog[] = "#include <math.h> \n#include <stdio.h>\n";
    sprintf(buf, "int x = %.10g\n", a);
    char m[] = "int main() {\n";
    char* prog_main = argv[1];
    char end[] = "}";
    int fd = open("lol.c", O_CREAT | O_TRUNC| O_RDWR, 0700);
    write(fd, prog, strlen(prog));
    write(fd, buf, strlen(buf));
    write(fd, m, strlen(m));
    write(fd, prog_main, strlen(prog_main));
    write(fd, end, strlen(end));
    char* const name[] = { "gcc", "2.c", "-o", "2", "", NULL };
    execve("./lol.py", name, environ);
}
