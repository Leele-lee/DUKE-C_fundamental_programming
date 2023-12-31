#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findMaxFrequency (int frequency[], int size) {
  int maxIndex = 0;
  for (int i = 1; i < size; i++) {
    if (frequency[i] > frequency[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}



void decrypt(FILE * f) {
  int frequency[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)){
      c = tolower(c);
      frequency[c - 'a']++;
    }
  }
  int index = findMaxFrequency(frequency, 26);
  char cryptChar = 'a' + index;
  //int decryptKey = abs('e' - cryptChar);
  int decryptKey = cryptChar - 'e';

  // if decryptKey < 0, need add 20s add not direct return decryptKey < 0
  if (decryptKey < 0) {
    decryptKey = 26 - 'e' + cryptChar;
  }
  if (decryptKey < 0 || decryptKey >= 26) {
    perror("encryp key is beyond the range [0, 26)");
  }
  fprintf(stdout, "%d\n", decryptKey);
}




int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
