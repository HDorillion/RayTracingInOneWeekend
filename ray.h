#pragma once

#include "vec3.h"

// A 3-D directional ray, with an origin and direction
class ray {
    point3 _origin;
    vec3 _direction;

public:
    ray() = delete;
    ray(const point3& origin, const vec3& direction)
        : _origin(origin), _direction(direction)
    {}

    point3 origin() const { return _origin; }
    vec3 direction() const { return _direction; }

    // Returns the point on the line at t
    point3 at(double t) const {
        return _origin + (t * _direction);
    }
};
