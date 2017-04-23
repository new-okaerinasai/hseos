#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

extern char** environ;

int main(int argc, char* argv[]) {
    int program = open("script.py", O_WRONLY|O_TRUNC|O_CREAT, 0700);
    char prog[] = "#!/usr/bin/python\nprint(";
    char mul[] = "*";
    char end_prog[] = "1)";
    char* const name[] = { "./script.py", NULL };
    write(program, prog, sizeof(prog) - 1);
    for (int i = 1; i != argc; ++i) {
        write(program, argv[i], strlen(argv[i]));
        write(program, mul, sizeof(mul) - 1);
    }
    write(program, end_prog, sizeof(end_prog));
    close(program);
    execve("./script.py", name, environ);   
}