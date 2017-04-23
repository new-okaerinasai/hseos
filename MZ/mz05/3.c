#include <stdio.h>
extern void myexp(double x, double* r);
int main() {
	double r = 0;
	myexp(-1, &r);
	printf("%.10g\n", r);
}