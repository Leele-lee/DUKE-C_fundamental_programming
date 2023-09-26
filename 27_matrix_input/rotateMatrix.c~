#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_SIZE 12

void rotate(char matrix[10][10]) {
  char copyM[10][10];
  memcpy(copyM, matrix, sizeof(matrix[0][0]) * 10 * 10);
  int startX = 9;
  for (int i = 0; i < 10; i++) {
    int startY = i;
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = copyM[startX-i][startY-j];
      startX -= 1;
      startY += 1;
    }
    startX += 11;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char oneLine[LINE_SIZE];
  int lines = 0;
  while (fgets(oneLine, LINE_SIZE, f) != NULL) {
    if (lines >= 10) {
      fprintf(stderr, "TOO MANY LINES");
      return EXIT_FAILURE;
    }
    if (strchr(oneLine, '\n') == NULL) {
      fprintf(stderr, "LINE IS TOO LONG");
      return EXIT_FAILURE;
    }
    if (strchr(oneLine, '\n') - oneLine != 10) {
      fprintf(stderr, "LINE IS TOO SHORT");
    }
    
    for (int j = 0; j < 10; j++) {
      matrix[lines][j] = oneLine[j];
    }
    lines++;
  }
  if (lines < 10) {
    fprintf(stderr, "NOT ENOUGH LINES");
  }
  rotate(matrix);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
