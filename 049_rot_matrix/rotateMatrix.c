#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 10

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Error. Function takes one argument!\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file. Booooo!\n");
    return EXIT_FAILURE;
  }

  //read matrix
  char line[LINE_SIZE + 2];
  int c = 0;
  int w = 0;
  char matrix[LINE_SIZE][LINE_SIZE + 2];
  size_t rows = 0;
  while (fgets(line, LINE_SIZE + 2, f) != NULL) {
    if (rows >= LINE_SIZE) {
      fprintf(stderr, "Oh no! Your matrix is too big\n");
      return EXIT_FAILURE;
    }
    if (strchr(line, '\n') == NULL) {  // If cant fined end of line, line = too long
      fprintf(stderr, "Too many columns! NOO.\n");
      return EXIT_FAILURE;
    }
    for (size_t cols = 0; cols < (LINE_SIZE + 2); cols++) {
      matrix[rows][cols] = line[cols];
      c = line[cols];
      if (c >= 32) {
        w++;
      }
    }
    rows++;
  }

  if ((rows != LINE_SIZE) || (w != 100)) {
    fprintf(stderr, "Bad news! More or less rows or columns.\n");
    return EXIT_FAILURE;
  }
  //rotate matrix
  char matrix_rot[LINE_SIZE][LINE_SIZE + 1];
  for (size_t x = 0; x < LINE_SIZE; x++) {
    for (size_t y = 0; y < LINE_SIZE; y++) {
      matrix_rot[x][y] = matrix[LINE_SIZE - y - 1][x];
    }
    matrix_rot[x][LINE_SIZE] = '\n';
  }

  //print matrix
  for (size_t i = 0; i < LINE_SIZE; i++) {
    for (size_t j = 0; j < LINE_SIZE + 1; j++) {
      fprintf(stdout, "%c", matrix_rot[i][j]);
    }
  }

  //close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file. Booo!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
