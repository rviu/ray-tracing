#pragma once

#include "vec3.h"

class ray {
private:
  point3 origin;
  vec3 direction;

public:
  ray() {}

  ray(const point3& origin, const vec3& direction) {
    this->origin = origin;
    this->direction = direction;
  }

  point3 get_origin() const { return origin; }
  vec3 get_direction() const { return direction; }

  point3 at(double t) const {
    return origin + t * direction;
  }
};
