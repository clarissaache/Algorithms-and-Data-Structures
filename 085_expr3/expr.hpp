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
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return n; }
};

class OpExpressions : public Expression {
 public:
  Expression * left;
  Expression * right;
  std::string sign;
  virtual ~OpExpressions() {
    delete left;
    delete right;
  };
  OpExpressions(Expression * lhs, Expression * rhs) : left(lhs), right(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(";
    ss << left->toString() << sign << right->toString();
    ss << ")";
    return ss.str();
  }
  virtual long evaluate() const = 0;
};

class PlusExpression : public OpExpressions {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpressions(lhs, rhs) {
    sign = " + ";
  }
  virtual long evaluate() const { return left->evaluate() + right->evaluate(); };
};
class MinusExpression : public OpExpressions {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpressions(lhs, rhs) {
    sign = " - ";
  }
  virtual long evaluate() const { return left->evaluate() - right->evaluate(); };
};

class TimesExpression : public OpExpressions {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpressions(lhs, rhs) {
    sign = " * ";
  }
  virtual long evaluate() const { return left->evaluate() * right->evaluate(); };
};

class DivExpression : public OpExpressions {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpressions(lhs, rhs) {
    sign = " / ";
  }
  virtual long evaluate() const { return left->evaluate() / right->evaluate(); };
};
