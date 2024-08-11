#ifndef RAYTRACER_HITTABLE_LIST_H
#define RAYTRACER_HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list();
    explicit hittable_list(const std::shared_ptr<hittable>& object);
    void clear();
    void add(const std::shared_ptr<hittable>& object);
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

};

#endif //RAYTRACER_HITTABLE_LIST_H
