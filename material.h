#pragma once

#include "util.h"

struct hit_record;

class material {
public:
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const = 0;
};

class lambertian : public material {
private:
  color albedo;

public:
  lambertian(const color& a) : albedo(a) {}

  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const override {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;

    return true;
  }
};

class metal : public material {
private:
  color albedo;
  double fuzz;

public:
  metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const override {
    vec3 reflected = reflect(get_unit_vector(r_in.get_direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;

    return (dot_product(scattered.get_direction(), rec.normal) > 0);
  }
};
