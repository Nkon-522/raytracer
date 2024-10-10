#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <utility>

#include "hittable.h"

class sphere final : public hittable {
private:
    ray center;
    float radius;
    std::shared_ptr<material> mat;
public:
    sphere(const point3& static_center, float radius, std::shared_ptr<material> mat);
    sphere(const point3& center1, const point3& center2, float radius, std::shared_ptr<material> mat);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif //RAYTRACER_SPHERE_H
