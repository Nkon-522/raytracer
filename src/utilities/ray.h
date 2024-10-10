#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.h"

class ray {
private:
    point3 orig;
    vec3 dir;
    double tm;
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction) : ray{origin, direction, 0} {}
    ray(const point3& origin, const vec3& direction, const float& time) : orig{origin}, dir{direction}, tm{time} {}

    [[nodiscard]] const point3& origin() const  { return orig; }
    [[nodiscard]] const vec3& direction() const { return dir; }
    [[nodiscard]] double time() const { return tm; }

    [[nodiscard]] point3 at(const float& t) const {
        return orig + t*dir;
    }
};

#endif //RAYTRACER_RAY_H
