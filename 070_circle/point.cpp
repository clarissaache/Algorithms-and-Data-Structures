#include "point.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <cmath>

void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
}
