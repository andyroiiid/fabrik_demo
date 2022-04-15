//
// Created by Andrew Huang on 4/15/2022.
//

#ifndef FABRIK_DEMO_MATH_H
#define FABRIK_DEMO_MATH_H

#include <cmath>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    inline Vec2 operator+(const Vec2 &rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    inline Vec2 operator-(const Vec2 &rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    inline Vec2 operator*(float s) const {
        return {x * s, y * s};
    }

    inline Vec2 operator/(float s) const {
        return {x / s, y / s};
    }

    [[nodiscard]] inline float dot(const Vec2 &rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    [[nodiscard]] inline float lengthSquared() const {
        return dot(*this);
    }

    [[nodiscard]] inline float length() const {
        return sqrtf(lengthSquared());
    }

    [[nodiscard]] inline Vec2 normalize() const {
        return *this / length();
    }
};

static inline Vec2 operator*(float s, const Vec2 &v) { return v * s; }

#endif //FABRIK_DEMO_MATH_H
