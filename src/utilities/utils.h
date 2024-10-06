#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#include <limits>
#include <random>

// Constants

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385;

inline std::random_device rd;
inline std::mt19937 generator(rd());
inline std::uniform_real_distribution<float> distribution(0.0, 1.0);

// Utility Functions

inline float degrees_to_radians(const float& degrees) {
    return degrees * pi / 180.0f;
}

inline float random_float() {
    // Return random real in [0, 1)
    return distribution(generator);
}

inline float random_float(const float& min, const float& max) {
    // Return random real in [min, max)
    return min + (max - min) * random_float();
}

inline float linear_to_gamma(float linear_component)
{
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

#endif //RAYTRACER_UTILS_H
