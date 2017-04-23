#include <stdio.h>
/*int mystrspn(const char *s, const char *accept) {
	const char* x = s;
  	const char* begin = accept;
  	int k = 0;
  while(*x != '\0') {
  	while(*accept != '\0') {
    	if (*accept == *x) {
        	++k;
          	accept = begin;
          	break;
        }
      	if (*accept == '\0') {
        	return k;
        }
      accept++;
    }
    ++x;
  }
  return k;
}*/

extern int mystrspn(char* a, char* b);
int main() {
    char a[] = "12322";
    char b[] = "321lmao";
    printf("%d\n", mystrspn(a, b));
}