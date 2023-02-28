#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);  // prototype of function we want to test

int main(void) {
  int array1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int array2[] = {9, 8, 7, 1, 2, 3};
  int array4[] = {3, 3, 3, 3};
  int array6[] = {-2, -1, 0, 1, 16, 20, 50};
  //int array7[] = {5, 4, 3, 2, 1};
  //int array8[] = {5, 1, 6, 1, 7, 1, 8};
  //int array9[] = {100000, 2000, 4000, 5000};

  if (maxSeq(array1, 10) != 4) {
    printf("1nope!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array2, 6) != 3) {
    printf("2nope!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(NULL, 0) != 0) {
    printf("3nope!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, 4) != 1) {
    printf("4nope!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array1, 0) != 0) {
    printf("5nope!\n");
    return EXIT_FAILURE;
  }
  if (maxSeq(array6, 7) != 7) {
    printf("6nope!\n");
    return EXIT_FAILURE;
  }
  //if (maxSeq(array7, 5) != 1) {
  //return EXIT_FAILURE;
  //}
  //if (maxSeq(array8, 7) != 2) {
  //  return EXIT_FAILURE;
  //}
  //if (maxSeq(array9, 4) != 3) {
  //return EXIT_FAILURE;
  //}
  else {
    printf("all is good!\n");
  }
  return EXIT_SUCCESS;
}
