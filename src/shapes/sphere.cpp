#include "sphere.h"

#include <utility>

// CONSTRUCTOR
sphere::sphere(const point3 &static_center, const float radius, std::shared_ptr<material> mat): center{static_center, {0,0,0}}, radius{fmaxf(0,radius)}, mat{std::move(mat)} {}
sphere::sphere(const point3 &center1, const point3 &center2, const float radius, std::shared_ptr<material> mat): center{center1, center2 - center1}, radius{fmaxf(0,radius)}, mat{std::move(mat)} {}

// METHODS
bool sphere::hit(const ray &r, const interval ray_t, hit_record &rec) const {
    const point3 current_center = center.at(r.time());
    const vec3 oc = current_center - r.origin();
    const auto a = r.direction().length_squared();
    const auto h = dot(r.direction(), oc);
    const auto c = oc.length_squared() - radius*radius;

    const auto discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    const auto sqrt_result = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = static_cast<float>(h - sqrt_result) / a;
    if (!ray_t.surrounds(root)) {
        root = static_cast<float>(h + sqrt_result) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    const vec3 outward_normal = (rec.p - current_center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}


