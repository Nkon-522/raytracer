#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <limits>

// Constants

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385;

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}

#endif //RAYTRACER_UTILS_H
