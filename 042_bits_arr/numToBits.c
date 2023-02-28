#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int getNthBit(uint32_t number, int bit) {
  if (bit < 0 || bit >= 32) {
    printf("Bit %d is invalid\n", bit);
    exit(EXIT_FAILURE);
  }
  return (number & (1 << bit)) != 0;
}

void numToBits(uint32_t * nums, int nNums, int * bits, int nBits) {
  // if statement to check for # of bits is= nNums * 32
  if (nBits >= nNums * 32) {
    // uint32_t * p_num = &nums[0];

    int * p_bits = &bits[0];
    for (int a = 0; a < nNums; a++) {
      for (int b = 31; b >= 0; b--) {
        *p_bits = getNthBit(nums[a], b);
        p_bits++;
      }
    }
  }
  else {
    printf("Invalid call to numToBits! nBits is %d, nNums is %d\n", nBits, nNums);
  }
}

void doTest(uint32_t * nums, int n) {
  int bits[n * 32];
  numToBits(nums, n, bits, n * 32);
  for (int i = 0; i < n; i++) {
    printf(" %9d (%8X) => ", nums[i], nums[i]);
    for (int j = 0; j < 32; j++) {
      printf("%d", bits[i * 32 + j]);
    }
    printf("\n");
  }
}

int main(void) {
  uint32_t array1[] = {1, 2, 3, 4, 5, 15, 109};
  uint32_t array2[] = {123456789, 987654321};
  int bits[7 * 32 - 1];
  doTest(array1, 7);
  doTest(array2, 2);
  numToBits(array1, 7, bits, 7 * 32 - 1);
  return EXIT_SUCCESS;
}
