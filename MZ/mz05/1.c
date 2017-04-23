#include <stdio.h>

extern unsigned extract();

int main() {
	unsigned int a = extract(1, 0, 1);
	printf("%d\n", a);
}