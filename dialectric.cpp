#include "dialectric.h"

bool Dialectric::scatter(
    const ray& r_in, const intersection_record& record, color& attenuation, ray& scattered_ray
) const {
    attenuation = color(1.0, 1.0, 1.0);
    double etai_over_etat =
        // Facing front
        (static_cast<int>
        (record.faces_front) * 1.0 / ref_ind)
        + // Or not facing front
        (static_cast<int>
        (!record.faces_front) * ref_ind);
    vec3 unit_direction = unit_vector(r_in.direction());
    // Follow Snell's Law to determine if reflection or refraction
    double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    // Calculate rays
    if (etai_over_etat * sin_theta > 1.0) { // Reflect
        vec3 reflected_ray = reflect(unit_direction, record.normal);
        scattered_ray = ray(record.p, reflected_ray);
        return true;
    }
    else { // Refract
        vec3 refracted_ray =
            refract(unit_direction, record.normal, etai_over_etat);
        scattered_ray = ray(record.p, refracted_ray);
        return true;
    }
}
