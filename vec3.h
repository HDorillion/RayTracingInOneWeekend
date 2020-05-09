#pragma once

#include "utilities.h"

#include <cmath>
#include <iostream>

using std::sqrt;

// A 3-D vector
class vec3
{
    double e[3] = { 0, 0, 0 };
public:
    vec3() {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[1]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    void correct_gamma(double scale) {
        e[0] = sqrt(scale * e[0]);
        e[1] = sqrt(scale * e[1]);
        e[2] = sqrt(scale * e[2]);
    }

    double length() const { return sqrt(length_squared()); }
    double length_squared() const {
        return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
    }

    inline static vec3 random() {
        return vec3{ random_double(), random_double(), random_double() };
    }

    inline static vec3 random(double min, double max) {
        return vec3{
            random_double(min, max),
            random_double(min, max),
            random_double(min, max) };
    }
};

using point3 = vec3;
using color = vec3;

// Utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.x() * v.x()
        + u.y() * v.y()
        + u.z() * v.z();
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(
        u.y() * v.z() - u.z() * v.y(),
        u.z() * v.x() - u.x() * v.z(),
        u.x() * v.y() - u.x() * v.y()
    );
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// ****************************************************************************
// Miscellaneous functions
// ****************************************************************************
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    auto a = random_double(0, 2 * pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

// Generates a random vector to the normal based on if it is in the same
// hemisphere
inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 unit_sphere = random_in_unit_sphere();
    auto is_in_same_hemisphere = (dot(unit_sphere, normal) > 0.0);
    return
        // In same hemisphere
        static_cast<int>(is_in_same_hemisphere) * unit_sphere
        + // Or not in same hemisphere
        static_cast<int>(!is_in_same_hemisphere) * -unit_sphere;
}

// Calculates a reflected ray about a vector, v, and a normal, n
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

// Calculates a refracted ray
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perpendicular = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perpendicular;
}
