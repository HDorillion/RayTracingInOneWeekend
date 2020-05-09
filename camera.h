#pragma once

#include "ray.h"

class Camera {
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

public:
    Camera()
        : lower_left_corner({ -2., -1., -1. })
        , horizontal({4., 0., 0.})
        , vertical({0.,2.,0.})
        , origin({0.,0.,0.})
    {}

    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
};
