#include <stdio.h>

extern int process();
unsigned int A = 2, B = 1, C = 5;
int main(){
	printf("%d\n", process(A, B, C));
}