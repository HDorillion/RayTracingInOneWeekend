#pragma once

#include "intersectable.h"
#include "material.h"
#include "vec3.h"

#include <memory>

// A Spherical object in 3-D space which can be intersected
class Sphere : public Intersectable {
    point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

public:
    Sphere() = delete;
    Sphere(point3 center, double radius, std::shared_ptr<Material> mat)
        : center(center), radius(radius), mat_ptr(mat) {}

    // Returns true if r intersects the sphere within the given range
    bool intersects(const ray& r, double t_min, double t_max, intersection_record& rec) const override;
};

bool Sphere::intersects(const ray& r, double t_min, double t_max, intersection_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        // The minus root
        auto temp = (-half_b - root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        // The plus root
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}