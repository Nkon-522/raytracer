#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <cmath>
#include <iostream>

#include "utils.h"

class vec3 {
public:
    float e[3];

    vec3() : e{0,0,0} {}
    vec3(const float e0, const float e1, const float e2) : e{e0, e1, e2} {}

    [[nodiscard]] float x() const { return e[0]; }
    [[nodiscard]] float y() const { return e[1]; }
    [[nodiscard]] float z() const { return e[2]; }

    vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(float t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(float t) {
        return *this *= 1/t;
    }

    [[nodiscard]] float length() const {
        return std::sqrt(length_squared());
    }

    [[nodiscard]] float length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random() {
        return {random_float(), random_float(), random_float()};
    }

    static vec3 random(const float min, const float max) {
        return {random_float(min,max), random_float(min,max), random_float(min,max)};
    }

};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(float t, const vec3& v) {
    return {t*v.e[0], t*v.e[1], t*v.e[2]};
}

inline vec3 operator*(const vec3& v, float t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, float t) {
    return (1/t) * v;
}

inline float dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1]
           + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return {u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (const auto length_square = p.length_squared(); 1e-160 < length_square && length_square <= 1)
            return p / static_cast<float>(sqrt(length_square));
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    if (const vec3 on_unit_sphere = random_unit_vector(); dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}


#endif //RAYTRACER_VEC3_H
