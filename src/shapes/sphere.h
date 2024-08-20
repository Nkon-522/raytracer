#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"

class sphere final : public hittable {
private:
    point3 center;
    float radius;
public:
    sphere(const point3& center, float radius);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif //RAYTRACER_SPHERE_H
