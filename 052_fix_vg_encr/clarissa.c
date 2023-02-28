#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void num_seq(int n) {
  int x = 3;
  int y = (2 * n) + 3;
  printf("%d ", n + 3);
  for (int i = 0; i < (n + 1); i++) {
    if (n % 2 == 0) {
      printf("%d ", x);
    }
    else {
      printf("%d ", y);
    }
    //Update x and y:
    if (i % 2 == 0) {
      x = x - 1;
      y = y + 1;
    }
    else {
      y = y + 2;
      x = x - 2;
    }
  }
  printf("\n");
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Needs one argument n\n");
    return EXIT_FAILURE;
  }
  int n = atoi(argv[1]);

  num_seq(n);
  return EXIT_SUCCESS;
}
