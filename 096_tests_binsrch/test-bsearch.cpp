#include <bits/stdc++.h>

#include <cstdlib>
#include <ostream>

#include "function.h"

//Function im going to test out
int binarySearchForZero(Function<int, int> * f, int low, int high);

// The class to count the times the search is invoked:
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  //Class Constructor:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  // Invoke Method:
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);  //RECURSIVE
  }
};

// Create child class of Function and write a "strictly increasing function"
class myFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

// Check function
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int call_count = 0;
  if (high > low) {
    call_count = log2(high - low) + 1;
  }
  else {
    call_count = 1;
  }
  //I dont understand this:
  CountedIntFn * wrapping_f =
      new CountedIntFn(call_count, f, mesg);  // Create an instance of the wrapper
  //Needs to be a pointer, dynamic dispatch?
  // Now I call the binary search using the wrapper instead of the function directly
  //...so it counts the calls??
  int my_ans = binarySearchForZero(wrapping_f, low, high);
  // This is now supposed to return the number of calls to f
  assert(my_ans == expected_ans);
}

// Create child class of Function and write a "strictly increasing function"
class DrewsFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

int main(void) {
  // test my function that is strictly increasing
  myFunction * test_function = new myFunction();
  check(test_function, -5, 1, 0, "find 0, odd range");
  check(test_function, 5, 10, 5, "cant find 0 its all positive");
  check(test_function, -1, 0, -1, "0 is not included");
  check(test_function, 0, 1, 0, "zero is the low boundary");
  DrewsFunction * test2_function = new DrewsFunction();
  check(test2_function, 0, 150000, 52359, "less than 20 invocations need to happen");
  check(test_function, -10, -3, -4, "all negative, no 0");
  check(test_function, 0, 400000, 0, "return in less than 20, when 0 is low");
  check(test_function, 1, 400000, 1, "return in less than 20, when all possitive");
  check(test_function, -40000, 0, -1, "return in less than 20, when 0 is not included");
  check(test_function, -10, -10, -10, "range is 0");
  check(test_function, 10, 10, 10, "range is 0 all positive");
  check(test_function, -2, 4, 0, "even range");
  return EXIT_SUCCESS;
}
