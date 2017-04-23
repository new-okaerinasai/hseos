extern unsigned int satsum(unsigned int a, unsigned int b);
#include <stdio.h>

unsigned int a, b;
int main() {
	scanf("%u%u", &a, &b);
	printf("%u\n", satsum(a, b));
}