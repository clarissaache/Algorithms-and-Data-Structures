#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D::initVector(double x_init, double y_init) {
  x = x_init;
  y = y_init;
}

double Vector2D::getMagnitude() const {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}

double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}
