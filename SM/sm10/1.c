#include <stdio.h>
unsigned long long int A = ((3ULL) << 33), B = ((1ULL) << 31);

extern void process();
int main() {
	process();
	unsigned long long c = A * 2 - B / 2;
	printf("%llu %llu %llu\n", A, B, c);
}
