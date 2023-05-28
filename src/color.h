#pragma once

#include <iostream>

#include "vec3.h"

void print_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  double scale = 1.0 / samples_per_pixel;
  r = std::sqrt(scale * r);
  g = std::sqrt(scale * g);
  b = std::sqrt(scale * b);

  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}
