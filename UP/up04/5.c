#include <stdio.h>

extern void process(unsigned* data, int count);
int main() {
	unsigned data[] = { 5, 2, 3, 4, 1 };
	int a = 1;
	int b = 4;
	process(data, 5);
	for (int i = 0; i != 5; ++i) {
		printf("%u ", data[i]);
	}
}