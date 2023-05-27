#include <iostream>
#include <cmath>

#include "vec3.h"
#include "color.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 ray_origin_to_sphere_center = r.get_origin() - center;

  double a = r.get_direction().length_squared();
  double half_b = dot_product(ray_origin_to_sphere_center, r.get_direction());
  double c = ray_origin_to_sphere_center.length_squared() - radius * radius;

  double discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

color get_ray_color(const ray& r) {
  double t = hit_sphere(point3(0, 0, -1), 0.5, r);

  if (t > 0.0) {
    vec3 normal = get_unit_vector(r.at(t) - vec3(0, 0, -1));
    return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  vec3 unit_direction = get_unit_vector(r.get_direction());
  t = 0.5 * (unit_direction.y() + 1.0);

  color gradient_start = color(1.0, 1.0, 1.0);
  color gradient_end = color(0.5, 0.7, 1.0);

  return (1.0 - t) * gradient_start + t * gradient_end;
}

int main() {
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;

  vec3 origin = point3(0, 0, 0);
  vec3 horizontal = vec3(viewport_width, 0, 0);
  vec3 vertical = vec3(0, viewport_height, 0);
  vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    int progress = 100 * (double(image_height - j) / image_height);
    std::cerr << "\rProgress: " << progress << "%" << std::flush;

    for (int i = 0; i < image_width; i++) {
      double u = double(i) / (image_width - 1);
      double v = double(j) / (image_height - 1);

      ray r(origin,
            lower_left_corner + u * horizontal + v * vertical - origin);

      color pixel_color = get_ray_color(r);
      print_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nRendering Complete!\n";
}
