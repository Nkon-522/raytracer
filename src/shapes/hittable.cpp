#include "hittable.h"

// CONSTRUCTOR
hit_record::hit_record(): t{}, front_face{} {}

hittable::~hittable() = default;

// METHODS
[[maybe_unused]] void hit_record::set_face_normal(const ray &r, const vec3 &outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}