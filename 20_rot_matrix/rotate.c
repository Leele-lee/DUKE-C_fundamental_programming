#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
