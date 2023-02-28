#include <stdio.h>
#include <stdlib.h>

#include "point.hpp"

class Circle {
 private:
  Point p;
  const double r;

 public:
  // value constructor (asked for)
  Circle(Point a, const double b) : p(a), r(b){};
  // default constructor (for sanity)
  Circle() : p(), r(0){};
  // Move circle center
  void move(double dx, double dy);
  // Compute the area of the intersection of two circles
  double intersectionArea(const Circle & otherCircle);
};
