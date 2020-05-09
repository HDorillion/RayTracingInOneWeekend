#pragma once

namespace settings {
    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 384;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 50;
    constexpr int max_depth = 25;
}
