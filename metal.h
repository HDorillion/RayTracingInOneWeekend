#pragma once

#include "material.h" // Base class

#include "color.h"
#include "intersectable.h"

// A shiny material with metallic characteristics
class Metal : public Material {
    color albedo;
    double fuzz;

public:
    Metal(const color& a, double fuzz)
        : albedo(a), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        const ray& r_in,
        const intersection_record& record,
        color& attenuation,
        ray& scattered_ray
    ) const override {
        vec3 reflected_ray = reflect(
            unit_vector(r_in.direction()), record.normal
        );
        scattered_ray = ray(
            record.p,
            reflected_ray + fuzz * random_in_unit_sphere()
        );
        attenuation = albedo;
        return (dot(scattered_ray.direction(), record.normal) > 0);
    }
};