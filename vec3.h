#pragma once

#include <iostream>
#include <cmath>
#include <vector>

#include "util.h"

class vec3 {
private:
  double e[3];

public:
  vec3() : e{0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  vec3& operator+=(const vec3 &v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();

    return *this;
  }

  vec3& operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
  }

  vec3& operator/=(const double t) {
    return *this *= 1/t;
  }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  double length() const {
    return std::sqrt(length_squared());
  }

  inline static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  inline static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }

  bool near_zero() const {
    const auto s = 1e-8;
    return (fabs(e[0] < s))
        && (fabs(e[1] < s))
        && (fabs(e[2] < s));
  }
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
  return out << v.x() << " " << v.y() << " " << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3 &v) {
  return vec3(t*v.x(), t*v.y(), t*v.z());
}

inline vec3 operator*(const vec3 &v, double t) {
  return t * v;
}

inline vec3 operator/(vec3 v, double t) {
  return (1/t) * v;
}

inline double dot_product(const vec3 &u, const vec3 &v) {
  return u.x() * v.x()
       + u.y() * v.y()
       + u.z() * v.z();
}

inline vec3 cross_product(const vec3 &u, const vec3 &v) {
  return vec3(u.y() * v.z() - u.z() * v.y(),
              u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

inline vec3 get_unit_vector(vec3 v) {
  return v / v.length();
}

inline vec3 random_in_unit_sphere() {
  while (true) {
    point3 p = vec3::random(-1, 1);
    if (p.length_squared() >= 1) continue;

    return p;
  }
}

inline vec3 random_unit_vector() {
  return get_unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
  vec3 in_unit_sphere = random_in_unit_sphere();

  if (dot_product(in_unit_sphere, normal) > 0.0) {
    return in_unit_sphere;
  } else {
    return -in_unit_sphere;
  }
}

inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot_product(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  double cos_theta = fmin(dot_product(-uv, n), 1.0);
  vec3 r_out_perpendicular = etai_over_etat * (uv + cos_theta * n);
  vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perpendicular.length_squared())) * n;

  return r_out_parallel + r_out_parallel;
}

inline vec3 random_in_unit_disk() {
  while (true) {
    point3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.length_squared() >= 1) continue;

    return p;
  }
}
