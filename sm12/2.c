
#include <stdio.h>
double A = 22, B = 3, C = 0;
extern void process();
int main() {
	process();
	printf("%.10g\n", C);
}