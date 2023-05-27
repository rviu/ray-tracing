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
