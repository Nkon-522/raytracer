#ifndef RAYTRACER_HELPER_H
#define RAYTRACER_HELPER_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Using

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif //RAYTRACER_HELPER_H
