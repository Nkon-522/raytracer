#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

#include "helper.h"

class interval {
public:
    float min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(float min, float max) : min(min), max(max) {}

    float size() const {
        return max - min;
    }

    [[nodiscard]] bool contains(float x) const {
        return min <= x && x <= max;
    }

    [[nodiscard]] bool surrounds(float x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

inline const interval interval::empty    = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);

#endif //RAYTRACER_INTERVAL_H
