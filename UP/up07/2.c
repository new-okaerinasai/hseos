#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    double num;
    scanf("%lg", &num);
    FILE* pre = fopen("lmao.c", "w");
    fprintf(pre, "#include <math.h> \n#include <stdio.h>\n");
    fprintf(pre, "double x = %.10g;\n", num);
    fprintf(pre, "int main() {\n");
    fprintf(pre, "double result = (\n");
    fprintf(pre, "%s\n", argv[1]);
    char tmp[] = "%.10g";
    fprintf(pre, ");\n printf(\"%s\\n\", result); }\n", tmp);
    fclose(pre);
    if (!fork()) {
        execlp("gcc", "gcc", "lmao.c", "-o", "lmao", "-lm", NULL);
    }
    wait(NULL);
    execlp("./lmao", "./lmao", NULL);
}
