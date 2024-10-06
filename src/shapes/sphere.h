#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <utility>

#include "hittable.h"

class sphere final : public hittable {
private:
    point3 center;
    float radius;
    std::shared_ptr<material> mat;
public:
    sphere(const point3& center, float radius, std::shared_ptr<material> mat);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif //RAYTRACER_SPHERE_H
