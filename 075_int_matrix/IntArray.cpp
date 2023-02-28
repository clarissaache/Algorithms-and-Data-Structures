#include "IntArray.h"

#include <assert.h>

#include <ostream>

//(1) DEFAULT CONSTRUCTOR
IntArray::IntArray() : data(NULL), numElements(0) {
}

//(2) CONSTRUCTOR THAT INIT SIZE TO n
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

//(3) COPY CONSTRUCTOR
// copies the left (this) to the right
IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]), numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
// (4) DESTRUCTOR
IntArray::~IntArray() {
  delete[] data;
}
// (5) ASSIGNMENT OPERATOR TO COPY
//copies the right (after = sign) to the left (this)
IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}
// (6) POSITION "[]" OPERATOR w const
const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  return this->data[index];
}

// (7) POSITION "[]" OPERATOR
int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  return data[index];
}
// (8) SIZE OF ARRAY
int IntArray::size() const {
  return numElements;
}
// (9) EQUALITY "==" OPERATOR
bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 0;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 0;
    }
  }
  return 1;  //true if no differences are found
}

//(10) INEQUALITY "!=" OPERATOR
bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 1;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 1;
    }
  }
  return 0;  //false is no differences are found
}
// (11) STREAM INSERTION OVERLOAD
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    if (i != rhs.size() - 1) {
      s << rhs[i] << ", ";
    }
    else {
      s << rhs[i];
    }
  }
  s << "}";
  return s;
}
// (12) SUM
IntArray IntArray::operator+(const IntArray & rhs) {
  assert(numElements == rhs.numElements);
  IntArray total(numElements);
  for (int i = 0; i < numElements; i++) {
    total.data[i] = rhs.data[i] + data[i];
  }
  return total;
}
