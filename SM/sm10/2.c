#include <stdio.h>
double a = 3.0, b = 4.0, r;
extern void myhypot(double a, double b, double* r);
int main() {
	myhypot(a, b, &r);
	printf("%.10g\n", r);
}