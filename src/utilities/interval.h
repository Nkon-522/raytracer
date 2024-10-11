#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

#include "utils.h"

#include <algorithm>

class interval {
public:
    float min, max;

    interval() : min{+infinity}, max{-infinity} {} // Default interval is empty

    interval(const float min, const float max) : min{min}, max{max} {}

    interval(const interval& a, const interval& b) {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    [[nodiscard]] float size() const {
        return max - min;
    }

    [[nodiscard]] bool contains(const float& x) const {
        return min <= x && x <= max;
    }

    [[nodiscard]] bool surrounds(const float& x) const {
        return min < x && x < max;
    }

    [[nodiscard]] float clamp(const float& x) const {
        return std::clamp(x, min, max);
    }

    [[nodiscard]] interval expand(const float& delta) const {
        const auto padding = delta/2;
        return {min - padding, max + padding};
    }

    static const interval empty, universe;
};

inline const interval interval::empty     {interval{+infinity, -infinity}};
inline const interval interval::universe  {interval{-infinity, +infinity}};

#endif //RAYTRACER_INTERVAL_H
