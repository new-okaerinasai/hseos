#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char buf[222];
    char buf1[300];
    scanf("%s", buf1);
    char prog[] = "#include <math.h> \n#include <stdio.h>\n";
    sprintf(buf, "double x = %s;\n", buf1);
    char m[] = "int main() {\n";
    char end[] = "}";
    int fd = open("lol.c", O_CREAT | O_TRUNC| O_RDWR, 0700);
    char end_main_p[] = ");\n printf(\"%.10g\\n\", result);\n";
    char main_p[] = "double result = (";
    write(fd, prog, strlen(prog));
    write(fd, buf, strlen(buf));
    write(fd, m, strlen(m));
    write(fd, main_p, strlen(main_p));
    write(fd, argv[1], strlen(argv[1]));
    write(fd, end_main_p, strlen(end_main_p));
    write(fd, end, strlen(end));
    close(fd);
    if (!fork()) {
        execlp("gcc", "gcc", "lol.c", "-o", "lol", "-lm", NULL);
    }
    wait(NULL);
    execlp("./lol", "./lol", NULL);
}