#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


//you will want to open the file, read the lines of text, split them into
//key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
//each time), close the file, and return the kvarray_t * that has your array.
kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL; //Could not open file->indicate failure
  }
  kvarray_t * kvArray = malloc(sizeof(*kvArray));
  kvArray->kvpair = NULL;
  kvArray->numKvpairs = 0;
  size_t sz = 0;
  char * line = NULL;
  size_t i = 0;
  char * value = NULL;
  while (getline(&line, &sz, f) >= 0) {
    
    kvpair_t * currPair = malloc(sizeof(*currPair));
  }
  
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
}