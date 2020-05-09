#pragma once

#include "material.h" // base class

#include "intersectable.h"
#include "color.h"

// A matte material with simple diffusion scattering
class Lambertian : public Material {
    color albedo;

public:
    Lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const intersection_record& record,
        color& attenuation, ray& scattered_ray
    ) const override {
        vec3 scatter_direction = record.normal + random_unit_vector();
        scattered_ray = ray(record.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};
