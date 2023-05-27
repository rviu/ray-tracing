#include <iostream>
#include <cmath>

#include "util.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color get_ray_color(const ray& r, const hittable& world, int depth) {
  hit_record rec;

  if (depth <= 0) {
    return color(0, 0, 0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    point3 target = rec.p + rec.normal + random_unit_vector();
    return 0.5 * get_ray_color(ray(rec.p, target - rec.p), world, depth - 1);
  }

  vec3 unit_direction = get_unit_vector(r.get_direction());
  double t = 0.5 * (unit_direction.y() + 1.0);

  color gradient_start = color(1.0, 1.0, 1.0);
  color gradient_end = color(0.5, 0.7, 1.0);

  return (1.0 - t) * gradient_start + t * gradient_end;
}

int main() {
  // Image
  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera
  camera cam;

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    int progress = 100 * (double(image_height - j) / image_height);
    std::cerr << "\rProgress: " << progress << "%" << std::flush;

    for (int i = 0; i < image_width; i++) {
      color pixel_color(0, 0, 0);

      for (int s = 0; s < samples_per_pixel; s++) {
        double u = (i + random_double()) / (image_width - 1);
        double v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += get_ray_color(r, world, max_depth);
      }

      print_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nRendering Complete!\n";
}
