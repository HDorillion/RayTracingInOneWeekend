#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

constexpr auto infinity = std::numeric_limits<double>::infinity();
constexpr auto pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

// Returns a random real in [0,1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Returns a random real in [min,max)
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
