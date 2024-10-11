#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include <memory>

#include "utilities/vec3.h"
#include "utilities/ray.h"
#include "utilities/interval.h"
#include "utilities/aabb.h"

class material;

class hit_record {
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    float t;
    bool front_face;

    hit_record();
    void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable {
public:
    virtual ~hittable();
    virtual bool hit(
        const ray& r, interval ray_t, hit_record& rec
    ) const = 0;
    [[nodiscard]] virtual aabb bounding_box() const = 0;
};

#endif //RAYTRACER_HITTABLE_H
