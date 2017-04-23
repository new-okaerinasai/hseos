#include <stdio.h>


char a[] = "lma1";
char b[] = "";
extern int mystrcmp(char* a, char* b);
int main() {
	int i = mystrcmp(a, b);
	printf("%d\n", i);
}
