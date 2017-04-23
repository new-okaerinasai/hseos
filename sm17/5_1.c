#include <stdio.h>
#include <string.h>

int main() {
	const char test[80], blah[80];
     const char *sep = " ";
     const char *word, *phrase, *brkt, *brkb;

     strcpy(test, "     TI PIDAR VSE TVOI DURZYA BOMZHI      ");

     for (word = strtok(test, sep);
          word;
          word = strtok(NULL, sep))
     {
         printf("%s\n", word);
     }
     printf("%s\n", test);
}