#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void freeEverything(char ** lines, size_t count) {
  for (size_t j = 0; j < count; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

char ** readLines(char ** data, FILE * stream, size_t * l) {
  char * current_line = NULL;
  size_t size = 0;
  *l = 0;
  while (getline(&current_line, &size, stream) >= 0) {
    data = realloc(data, (1 + *l) * sizeof(*data));
    if ((data == NULL) || (current_line == NULL)) {
      fprintf(stderr, "Cannot allocate memory in the heap\n");
      free(current_line);
      freeEverything(data, *l);
      exit(EXIT_FAILURE);
    };
    data[*l] = current_line;
    current_line = NULL;
    *l = *l + 1;
  }
  free(current_line);
  return data;
}

int main(int argc, char ** argv) {
  char ** lines = NULL;
  size_t count = 0;
  if (argc == 1) {
    //read from stdin stream:
    if (stdin == NULL) {
      fprintf(stderr, "Type something.\n");
      return EXIT_FAILURE;
    }
    lines = readLines(lines, stdin, &count);
    sortData(lines, count);
    freeEverything(lines, count);
  }
  if (argc > 1) {
    //read from each file provided as an arg to main:
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Can't open this file %s\n", argv[i]);
        freeEverything(lines, count);
        return EXIT_FAILURE;
      }
      // read, sort, and free all lines on a file:
      lines = readLines(lines, f, &count);
      sortData(lines, count);
      freeEverything(lines, count);
      lines = NULL;
      //close each file
      if (fclose(f) != 0) {
        fprintf(stderr, "Can't close this file %s\n", argv[i]);
        freeEverything(lines, count);
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
