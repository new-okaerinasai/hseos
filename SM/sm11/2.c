#include <stdio.h>

extern char nextchar();
extern int nc;

int main() {
	char c;
	for (int i = 0; i != 4101; ++i) {
		c = nextchar();
		printf("%d %d %d \n", c, nc, c == nc);
	}
}
