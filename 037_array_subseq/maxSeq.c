#include <stdio.h>
#include <stdlib.h>

size_t max(size_t a, size_t b) {
  if (a > b) {
    return a;
  }
  else {
    return b;
  }
}

size_t maxSeq(int * array, size_t n) {
  size_t count = 1;
  size_t max_count = 1;
  if (n == 0 || array == NULL) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) {
      count++;
    }
    else {
      max_count = max(count, max_count);
      count = 1;
    }
  }
  return max(count, max_count);
}
