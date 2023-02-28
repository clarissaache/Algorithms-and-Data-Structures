#include "circle.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#define PI 3.1415926535

void Circle::move(double dx, double dy) {
  p.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = p.distanceFrom(otherCircle.p);
  if (r >= 0 && otherCircle.r >= 0) {
    if (d > r + otherCircle.r) {
      return 0.0;
    }
    if (d <= std::abs(r - otherCircle.r)) {
      double A0 = PI * std::pow(r, 2);
      double A1 = PI * std::pow(otherCircle.r, 2);
      return r < otherCircle.r ? A0 : A1;
    }
    if (d == 0 && r && otherCircle.r) {
      return PI * std::pow(r, 2);
    }
    //distances
    const double a_distanceCenterFirst =
        (std::pow(r, 2) - std::pow(otherCircle.r, 2) + std::pow(d, 2)) / (2 * d);
    const double b_distanceCenterSecond = d - a_distanceCenterFirst;
    const double h_height =
        std::sqrt(std::pow(r, 2) - std::pow(a_distanceCenterFirst, 2));
    //angles
    const double alpha =
        std::fmod(std::atan2(h_height, a_distanceCenterFirst) * 2.0 + 2 * PI, 2 * PI);
    const double beta =
        std::fmod(std::atan2(h_height, b_distanceCenterSecond) * 2.0 + 2 * PI, 2 * PI);

    // Calculate areas
    const double A0 = std::pow(r, 2) / 2.0 * (alpha - std::sin(alpha));
    const double A1 = std::pow(otherCircle.r, 2) / 2.0 * (beta - std::sin(beta));

    return A0 + A1;
  }
  return 0;
}
