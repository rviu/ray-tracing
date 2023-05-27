#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
private:
  point3 center;
  double radius;
  std::shared_ptr<material> mat_ptr;

public:
  sphere() {}
  sphere(point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  vec3 oc = r.get_origin() - center;
  double a = r.get_direction().length_squared();
  double half_b = dot_product(oc, r.get_direction());
  double c = oc.length_squared() - radius * radius;

  double discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return false;
  }

  double sqrt_of_discriminant = std::sqrt(discriminant);

  double root = (-half_b - sqrt_of_discriminant) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + sqrt_of_discriminant) / a;
    if (root < t_min || root > t_max) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mat_ptr;

  return true;
}
