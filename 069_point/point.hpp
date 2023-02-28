#include <stdio.h>
#include <stdlib.h>
class Point {
 private:
  double x;
  double y;

 public:
  Point() : x(0), y(0){};
  // default constructor
  void move(double dx, double dy);
  // increase the point by dx and dy
  double distanceFrom(const Point & p);
  // disctance between 2 points
};
