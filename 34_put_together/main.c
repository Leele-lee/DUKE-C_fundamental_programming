#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"
#include <assert.h>

//compute the counts of  values that appear in a particular input file
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open the file\n");
    return NULL;
  }
  counts_t * c = createCounts();
  
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    strtok(line, "\n");
    char * value = lookupValue(kvPairs, line);
    addCount(c, value);
  }
  free(line);

  assert(fclose(f) == 0);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "program filename1 filename2 etc.\n");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    fprintf(stderr, "%s file can not open\n", argv[1]);
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      fprintf(stderr, "%s can not open\n", argv[i]);
      return EXIT_FAILURE;
    }
    //compute the output file name from argv[i] (call this outName)
    char * outName = malloc((strlen(argv[i]) + 8) * sizeof(*outName));
    strcpy(outName, argv[i]);
    strcat(outName, ".counts");
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    
    //print the counts from c into the FILE f
    //close f
    printCounts(c, f);

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
