#pragma once

#include "ray.h"

// Represents a record of an intersection
struct intersection_record {
    point3 p;
    vec3 normal;
    double t = 0.;
    bool faces_front = false;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        faces_front = dot(r.direction(), outward_normal) < 0;
        if (faces_front) {
            normal = outward_normal;
        }
        else {
            normal = -outward_normal;
        }
    }
};

// Effectively an interface
// Represents an object which may be intersected
class Intersectable {
public:
    virtual bool intersects(const ray& r, double t_min, double t_max, intersection_record& rec) const = 0;
};
