#include <stdio.h>

extern void hijack_rand();
int main() {
	srand(12);
	hijack_rand();
	int a = rand();
	printf("%d\n", a);
	a = rand();
	printf("%d\n", a);
}