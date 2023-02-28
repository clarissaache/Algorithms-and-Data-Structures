#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: need to provide a story template AND categories\n");
  }
  // Open file with template
  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Cannot open file: ");
    return EXIT_FAILURE;
  }
  // Allocate categories
  catarray_t * cats = parseWords(argv[1]);
  int flag = 0;
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
