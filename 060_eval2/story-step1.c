#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: need to provide a only ONE story template\n");
    return (EXIT_FAILURE);
  }
  // Open file with template
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cannot open file: ");
    return EXIT_FAILURE;
  }
  // Allocate categories
  catarray_t * cats = NULL;
  int flag = 0;
  // print template TEST
  size_t i;
  char ** lines = readTemplate(f, &i);
  for (size_t j = 0; j < i; j++) {
    lines[j] = replaceCategories(lines[j], cats, flag);
    fprintf(stdout, "%s", lines[j]);
    free(lines[j]);
  }
  // Free stuff
  free(cats);
  free(lines);

  //Close file with template
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
