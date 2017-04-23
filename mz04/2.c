#include <stdio.h>

extern int process(int a, int b, int* res);
int main() {
	int res = 12;
	printf("%d\n", process(50, 5, &res));
	printf("%d\n", res);
}
