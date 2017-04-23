#include <stdint.h>

extern void mul64p(uint64_t a, uint64_t b);

int main() {
	mul64p(0xFF0FFFFFCDFEBABE, 0xFFF0FFFFDDADBEEF);
}