#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

FILE * OpenTemplate(char * file) {
  // Open file with template
  FILE * f = fopen(file, "r");
  if (f == NULL) {
    perror("Cannot open file: ");
    exit(EXIT_FAILURE);
  }
  return f;
}

int main(int argc, char ** argv) {
  if (argc < 3 || argc > 4 || (argc == 4 && argv[1][1] != 'n')) {
    fprintf(stderr, "Usage: need to provide a story template AND categories\n");
    return EXIT_FAILURE;
  }
  FILE * f;
  catarray_t * cats;
  int flag = 0;
  // Allow non-repeated word option:
  if (argc == 4) {
    f = OpenTemplate(argv[3]);
    cats = parseWords(argv[2]);
    flag = 1;
  }
  if (argc == 3) {
    f = OpenTemplate(argv[2]);
    cats = parseWords(argv[1]);
    flag = 0;
  }
  // Replace words and refs
  size_t i;
  char ** lines = readTemplate(f, &i);
  for (size_t j = 0; j < i; j++) {
    lines[j] = replaceCategories(lines[j], cats, flag);
    fprintf(stdout, "%s", lines[j]);
    free(lines[j]);
  }

  //free stuff:
  free(lines);
  freeStuff(cats);

  //Close file with template
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
