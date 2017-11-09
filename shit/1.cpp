#include <vector>
#include <stdio.h>

int main() {
	std::vector<std::vector<double>> v(10000, std::vector<double>(10000, 0));
	printf("%llu\n", sizeof(v));
}