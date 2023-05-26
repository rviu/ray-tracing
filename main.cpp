#include <iostream>
#include <cmath>

#include "vec3.h"
#include "color.h"

int main() {
  // Image
  const int image_width = 256;
  const int image_height = 256;

  // Render
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    int progress = 100 * (double(image_height - j) / image_height);
    std::cerr << "\rProgress: " << progress << "%" << std::flush;

    for (int i = 0; i < image_width; i++) {
      color pixel_color(double(i) / (image_width - 1),
                        double(j) / (image_height - 1),
                        0.25);
      print_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nRendering Complete!\n";
}
