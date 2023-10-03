#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
#include <assert.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * aCountArray = malloc(sizeof(*aCountArray));
  aCountArray->countArray = NULL;
  aCountArray->arraySize = 0;
  aCountArray->countUnknown = 0;
  return aCountArray;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->countUnknown += 1;
    return;
  }
  for (int i = 0; i < c->arraySize; i++) {
    if (strcmp(c->countArray[i].string, name) == 0) {
      c->countArray[i].count += 1;
      return;
    }
  }
  c->countArray = realloc(c->countArray, (c->arraySize + 1) * sizeof(*c->countArray));
  //create new one count
  one_count_t * newOneCount = malloc(sizeof(*newOneCount));
  newOneCount->string = malloc((strlen(name) + 1) * sizeof(*newOneCount->string));
  strcpy(newOneCount->string, name);

  newOneCount->count = 1;

  c->countArray[c->arraySize] = *newOneCount; //has * depend on count_t struct has one_count_t * countArray
                                              //newOneCount if count_t struct has one_count_t ** countArray 
  c->arraySize += 1;
  
  //free(newOneCount->string);                                            
  free(newOneCount);
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->arraySize; i++) {
    fprintf(outFile, "%s: %d\n", c->countArray[i].string, c->countArray[i].count);
  }
  if (c->countUnknown != 0) {
    fprintf(outFile, "%s: %d\n", "<unknown>", c->countUnknown);
  }
  assert(fclose(outFile) == 0);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->arraySize; i++) {
    free(c->countArray[i].string);
    //free(c->countArray[i]); //can't free, because c->countArray[i] is not a pointer point to a one_count_t, itself is a one_count_t, so you cannot free, you free it in addCount
  }
  free(c->countArray);
  free(c);
}
