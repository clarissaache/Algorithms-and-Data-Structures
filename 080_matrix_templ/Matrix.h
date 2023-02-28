#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;  //vector of vectors
 public:
  // (1) Default Constructor
  Matrix<T>() : numRows(0), numColumns(0), rows(){};  //do I need to add the T here?
  // (2) The other constructor
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    // initialize each row:
    for (int i = 0; i < r; i++) {
      std::vector<T> one_row(numColumns);
      rows.push_back(one_row);
    }
  }
  // (3) Assignment operator: Looks like "this = rhs"
  Matrix<T> & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<std::vector<T> > temp(rhs.rows);  // creates a deep copy!
      rows.clear();
      rows = temp;
      numColumns = rhs.numColumns;
      numRows = rhs.numRows;
    }
    return *this;
  }
  // (4) Copy Constructor: looks like "this(rhs)"
  Matrix<T>(const Matrix<T> & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}
  // (5) Destructor
  ~Matrix(){};  // do I need to do rows.clear() ???

  // (6) Get number of rows
  int getRows() const { return numRows; }
  // (7) Get number of columns
  int getColumns() const { return numColumns; }
  // (8) Index "[]" operator
  std::vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return rows[index];
  }
  // (9) Same but with const
  const std::vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return rows[index];
  }
  // (10) Bool "==" operator
  bool operator==(const Matrix & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows || rows != rhs.rows) {
      // Yup! vectors have the != overloaded to compare each element
      return 0;
    }
    else {
      return 1;
    }
  }
  // (11) Sum + operator
  Matrix<T> operator+(const Matrix & rhs) const {
    assert(numColumns == rhs.numColumns);
    assert(numRows == rhs.numRows);
    // Create new matrix
    Matrix<T> total(rhs);
    // Sum each element, = total
    for (int m = 0; m < numRows; m++) {
      for (int n = 0; n < numColumns; n++) {
        total.rows[m][n] = rows[m][n] + rhs.rows[m][n];
      }
    }
    total.numColumns = numColumns;
    total.numRows = numRows;
    return total;
  }
};
// (12) Overload << operator for vector first
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
#endif
