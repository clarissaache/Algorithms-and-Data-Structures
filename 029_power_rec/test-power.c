#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);  // prototype 4 the function in next assignment

int main(void) {
  unsigned test1 = power(2, 3);
  unsigned test2 = power(2, 0);
  unsigned test3 = power(2, 1);
  unsigned test4 = power(5, 5);
  unsigned test5 = power(1, 10);
  unsigned test6 = power(0, 0);
  unsigned test7 = power(50, 3);
  if (test1 != 8) {
    printf(" 2 to the power of 3 is 8, not %u\n", test1);
    return EXIT_FAILURE;
  }
  if (test2 != 1) {
    printf("2 to the power of 0 is 1, not %u\n", test2);
    return EXIT_FAILURE;
  }
  if (test3 != 2) {
    printf("2 to the power of 1 is 2, not %u\n", test3);
    return EXIT_FAILURE;
  }
  if (test4 != 3125) {
    printf("5 to the power of 5 is 3125, not %u\n", test4);
    return EXIT_FAILURE;
  }
  if (test5 != 1) {
    printf("1 to the power of 10 is 1, not %u\n", test5);
    return EXIT_FAILURE;
  }
  if (test6 != 1) {
    printf("0 (worngly) to the power of 0 is 1, not %u\n", test6);
    return EXIT_FAILURE;
  }
  if (test7 != 125000) {
    printf("50 ^ 3 is 125000, not %u\n", test7);
    return EXIT_FAILURE;
  }
  printf("all is good!\n");
  return EXIT_SUCCESS;
}
