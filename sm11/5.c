#include <stdio.h>

int divide(int a) {
	int k, r;
	int result = 0;
	while (a > 8) {
      	k = a >> 3;
      	r = a - (k << 3);
      	result += k;
      	a = (k << 1) + k + r;
    }
    if (a >= 5)
    	result += 1;
    result /= 2;
    return result;
}
