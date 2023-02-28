#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  // Compute the counts of values that appear in a particular input file
  //
  // #1 - open file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cant open the file with names.\n");
    return NULL;
  }
  // #2 - Read lines of file
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  int i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    if (curr == NULL) {
      fprintf(stderr, "Cant read line\n");
      break;
    }
    //Strip the \n newline
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    // Instead of adding key, add value
    for (int l = 0; l < kvPairs->num_pairs; l++) {
      curr[strcspn(curr, "\n")] = '\0';
      if (!strcmp(curr, kvPairs->pair_array[l]->key)) {
        lines[i] = kvPairs->pair_array[l]->value;
        break;
      }
      else {
        lines[i] = NULL;
      }
    }
    free(curr);
    curr = NULL;
    i++;
  }
  free(curr);
  // i is the total count of lines!
  //
  // #3 - Count values of each "name" in my new Lines array
  counts_t * fileCounts = createCounts();
  for (int j = 0; j < i; j++) {
    addCount(fileCounts, lines[j]);
  }
  free(lines);
  if (fclose(f) != 0) {
    fprintf(stderr, "Cant flose the file\n");
    exit(EXIT_FAILURE);
  }
  return fileCounts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * array = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], array);

    //compute The output file name from argv[i] (call this outName)
    char * outfile = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outfile, "w");
    if (f == NULL) {
      printf("Cant open outfile\n");
      exit(EXIT_FAILURE);
    }
    free(outfile);
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Cant close outfile\n");
      return (EXIT_FAILURE);
    }
    //free the memory for outName and c
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(array);
  return EXIT_SUCCESS;
}
