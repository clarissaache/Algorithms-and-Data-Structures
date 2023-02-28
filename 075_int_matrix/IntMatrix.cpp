#include "IntMatrix.h"

// (1) Default Constructor
IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
// (2) Other contructor
IntMatrix::IntMatrix(int r, int c) :
    numRows(r), numColumns(c), rows(new IntArray *[r]()) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
// (3) Copy Constructor
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]()) {
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs.numColumns);
  }
  for (int m = 0; m < numRows; m++) {
    for (int n = 0; n < numColumns; n++) {
      (*rows[m])[n] = (*rhs.rows[m])[n];
    }
  }
}
// (4) Destructor
IntMatrix::~IntMatrix() {
  for (int m = 0; m < numRows; m++) {
    delete rows[m];
  }
  delete[] rows;
}
// (5) Assignment Operator
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    // Create a temp for rows thats equal to the rhs object:
    IntArray ** temp = new IntArray *[rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs.numColumns);
    }
    //Copy contents to temp
    for (int m = 0; m < rhs.numRows; m++) {
      for (int n = 0; n < rhs.numColumns; n++) {
        (*temp[m])[n] = (*rhs.rows[m])[n];
      }
    }
    // Delete old rows:
    for (int m = 0; m < numRows; m++) {
      delete rows[m];
    }
    delete[] rows;
    rows = temp;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
// (6) Returns  number of rows
int IntMatrix::getRows() const {
  return numRows;  //does it need to be a ref?
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index < numRows && index >= 0);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
    return 0;
  }
  for (int m = 0; m < numRows; m++) {
    for (int n = 0; n < numColumns; n++) {
      if ((*rows[m])[n] != (*rhs.rows[m])[n]) {
        return 0;
      }
    }
  }
  return 1;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns);
  assert(numRows == rhs.numRows);
  //Create new matrix
  IntMatrix total(rhs);
  // Sum each element, = total
  for (int m = 0; m < numRows; m++) {
    for (int n = 0; n < numColumns; n++) {
      (*total.rows[m])[n] = (*rhs.rows[m])[n] + (*rows[m])[n];
    }
  }
  total.numColumns = numColumns;
  total.numRows = numRows;
  return total;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << *rhs.rows[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
