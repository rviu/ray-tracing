#pragma once

#include "util.h"

class material;

struct hit_record {
  point3 p;
  vec3 normal;
  std::shared_ptr<material> mat_ptr;

  double t;
  bool front_face;

  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    if (dot_product(r.get_direction(), outward_normal) < 0) {
      front_face = true;
      normal = outward_normal;
    } else {
      front_face = false;
      normal = -outward_normal;
    }
  }
};

class hittable {
public:
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
