#include "hittable_list.h"

// CONSTRUCTOR
hittable_list::hittable_list(): objects{} {};

hittable_list::hittable_list(const std::shared_ptr<hittable> &object): hittable_list{} { add(object); };

// METHODS
void hittable_list::clear() {objects.clear();}

void hittable_list::add(const std::shared_ptr<hittable> &object) {
    objects.push_back(object);
    bbox = aabb(bbox, object->bounding_box());
}

bool hittable_list::hit(const ray &r, const interval ray_t, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (const auto& object : objects) {
        if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

aabb hittable_list::bounding_box() const {
    return bbox;
}

