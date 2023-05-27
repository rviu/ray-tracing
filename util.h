#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include "ray.h"
#include "vec3.h"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358979323846264;

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}
