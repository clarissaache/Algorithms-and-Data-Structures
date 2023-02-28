#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

class Expression {
 public:
  //virtual destructor
  virtual ~Expression(){};
  Expression(){};
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 public:
  long n;
  virtual ~NumExpression(){};
  NumExpression(long num) : n(num){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << n;
    return ss.str();
  }
};

class PlusExpression : public Expression {
 public:
  Expression * left;
  Expression * right;
  virtual ~PlusExpression() {
    delete left;
    delete right;
  };
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(";
    ss << left->toString() << " + " << right->toString();
    ss << ")";
    return ss.str();
  }
};
