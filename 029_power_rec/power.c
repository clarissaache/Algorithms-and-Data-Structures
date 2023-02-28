#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned ans, unsigned x, unsigned y) {
  if (y == 0) {
    return ans;
  }
  return power_helper(ans * x, x, y - 1);
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(1, x, y);
}
