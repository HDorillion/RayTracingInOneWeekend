#pragma once
#include "material.h" // Base class

class Dialectric :
    public Material
{
    double ref_ind;
public:
    Dialectric(double refractrive_index) : ref_ind(refractrive_index) {}

    virtual bool scatter(
        const ray& r_in, const intersection_record& record,
        color& attenuation, ray& scattered_ray
    ) const override;
};

