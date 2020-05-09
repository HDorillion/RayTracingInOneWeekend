#pragma once

#include "material.h" // Base class

#include "color.h"
#include "intersectable.h"

// A shiny material with metallic characteristics
class Metal : public Material {
    color albedo;

public:
    Metal(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in,
        const intersection_record& record,
        color& attenuation,
        ray& scattered_ray
    ) const override {
        vec3 reflected_ray = reflect(
            unit_vector(r_in.direction()), record.normal
        );
        scattered_ray = ray(record.p, reflected_ray);
        attenuation = albedo;
        return (dot(scattered_ray.direction(), record.normal) > 0);
    }
};