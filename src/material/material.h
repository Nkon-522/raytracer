#ifndef MATERIAL_H
#define MATERIAL_H

#include "shapes/hittable.h"

using color = vec3;

class material {
public:
    virtual ~material();
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const;
};

class lambertian: public material {
private:
    color albedo;
public:
    explicit lambertian(const color& albedo);
    bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
};

class metal : public material {
private:
    color albedo;
    float fuzz;
public:
    explicit metal(const color& albedo, const float& fuzz);
    bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
};

class dielectric: public material {
private:
    float refraction_index;

    static float reflectance(const float& cosine, const float& refraction_index);

public:
    explicit dielectric(float refraction_index);

    bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override;
};
#endif //MATERIAL_H
