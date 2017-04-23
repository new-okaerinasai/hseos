#include <stdio.h>

int min(int b, int d) {
	if (b > d) {
    	return d;
    } else {
      return b;
    }
}

int max(int a, int c) {
  if (c > a) {
    	return c;
  } else {
    return a;
  }
  
}
int main() {
    int a, b, c, d;
  	int result = 0;
	while (scanf("%d%d%d%d", &a, &b, &c, &d) != -1) {
    	c = max(a, c);
      	d = min(b, d);
        printf("%d %d\n", c, d);
      	if (d > c) {
          	result += d - c;
        }
    }
  printf("%d\n", result);
} 