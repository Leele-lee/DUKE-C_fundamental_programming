#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  int pre = array[0];
  int totalNum = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > pre) {
      totalNum += 1;
    }
    pre = array[i];
  }
  return totalNum;
}
