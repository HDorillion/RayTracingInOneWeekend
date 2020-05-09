#pragma once

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool faces_front;

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

class Intersectable {
public:
    virtual bool intersects(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
