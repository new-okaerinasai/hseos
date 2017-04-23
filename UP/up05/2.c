#include <stdio.h>
extern int addbe(int n, char* pa, char* pb, char* pc);
int main() {
	char a[] = { 255, 255, 255 };
	char b[] = { 5, 4, 2 };
	char c[3];
	int d = addbe(3, a, b, c);
	printf("%d \n", d);
	for (int i = 0; i != 3; ++i) {
		printf("%d ", c[i]);
	}
}