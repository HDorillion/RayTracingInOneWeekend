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
    vec3 refracted_ray = refract(unit_direction, record.normal, etai_over_etat);
    scattered_ray = ray(record.p, refracted_ray);
    return true;
}
