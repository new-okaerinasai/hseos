#include <stdio.h>

extern float dot_product(int n, float* a, float* b);
float a[] = { 1.5, 3.5};
float b[] = { -3.5, 1.0};

int main() {
	float result = dot_product(0, a, b);
	printf("%.10g\n", result);
}