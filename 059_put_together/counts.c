
#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //allocate memory for counts_t and initialize it (nothing been counted)
  counts_t * allCounts = malloc(sizeof(*allCounts));
  allCounts->how_many = 0;
  allCounts->unknowns = 0;
  allCounts->array_counts = malloc(sizeof(*allCounts->array_counts));
  return allCounts;
}

counts_t * createStringCount(const char * name, counts_t * c) {
  c->array_counts =
      realloc(c->array_counts, (c->how_many + 1) * sizeof(*c->array_counts));
  // Now allocate for a new string value pair:
  c->array_counts[c->how_many] = malloc(sizeof(*c->array_counts[c->how_many]));
  // Allocate for string
  c->array_counts[c->how_many]->string = strdup(name);
  //malloc((strlen(name) + 1) * sizeof(*c->array_counts[1 + c->how_many]->string));
  // Update string and counts ON CURRENT spot:
  //strcpy(c->array_counts[c->how_many]->string, name);
  c->array_counts[c->how_many]->string_counts = 1;
  c->how_many++;
  return c;
}

void addCount(counts_t * c, const char * name) {
  //increment the count for the corresponding name. Null names are <unknown>
  int i = 0;
  int done = 0;
  //if name is NULL:
  if (name == NULL) {
    c->unknowns++;
    done = 1;
  }
  //if name is already saved in array:
  while (i < c->how_many && done == 0) {
    if (!strcmp(name, c->array_counts[i]->string)) {
      done = 1;
      c->array_counts[i]->string_counts++;
    }
    i++;
  }
  //if not in array:
  if (done == 0) {
    c = createStringCount(name, c);
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //print to outfile
  for (int i = 0; i < c->how_many; i++) {
    fprintf(outFile,
            "%s: %d\n",
            c->array_counts[i]->string,
            c->array_counts[i]->string_counts);
  }
  if (c->unknowns > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknowns);
  }
}
void freeCounts(counts_t * c) {
  //free everything
  for (int i = 0; i < c->how_many; i++) {
    free(c->array_counts[i]->string);
    free(c->array_counts[i]);
  }
  free(c->array_counts);
  free(c);
}
