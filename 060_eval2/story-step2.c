#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: need to provide ONE file with categories\n");
    return EXIT_FAILURE;
  }
  // Open file with WORDS
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cannot open file: ");
    return EXIT_FAILURE;
  }
  // Read lines in file
  size_t i;
  char ** lines = readTemplate(f, &i);
  // Save Keys and Values where they belong
  catarray_t * cats = malloc(sizeof(*cats));

  cats->n = 0;
  cats->arr = malloc(sizeof(*cats->arr));
  for (size_t j = 0; j < i; j++) {
    char * key = saveKeyValue(lines[j], lines[j][0], ':');
    char * value = saveKeyValue(lines[j], ':', '\n');
    cats = saveCategories(key, value, cats);
    free(lines[j]);
    free(key);
    free(value);
  }
  // Print for Categories for Testing
  printWords(cats);

  //free stuff
  free(lines);
  freeStuff(cats);

  //Close file with template
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
