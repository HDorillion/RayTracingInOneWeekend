#pragma once

#include "utilities.h"
#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    // Scale pixel
    const auto scale = (1. / samples_per_pixel);
    pixel_color.correct_gamma(scale);
    // Output pixel
    const auto min = 0.0, max = 0.999;
    out << static_cast<int>(256 * clamp(pixel_color.x(), min, max)) << ' '
        << static_cast<int>(256 * clamp(pixel_color.y(), min, max)) << ' '
        << static_cast<int>(256 * clamp(pixel_color.z(), min, max)) << '\n';
}
