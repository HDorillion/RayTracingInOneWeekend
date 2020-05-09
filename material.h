#pragma once

#include "vec3.h"
#include "intersectable.h"
#include "ray.h"

// Interface for materials
// Requires method to scatter an incoming ray
class Material {
public:
    // Scatters the incomming ray with an attenuation color and scattered ray
    virtual bool scatter(
        const ray& r_in, const intersection_record& record,
        color& attenuation, ray& scattered_ray
    ) const = 0;
};