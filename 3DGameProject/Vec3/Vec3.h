#pragma once
#include <cmath>
#include "DxLib.h"   // ← これを必ず上に！

struct Vec3
{
    float x{}, y{}, z{};

    Vec3() = default;
    Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    operator VECTOR() const
    {
        VECTOR v;
        v.x = x;
        v.y = y;
        v.z = z;
        return v;
    }

    Vec3 operator+(const Vec3& rhs) const
    {
        return { x + rhs.x, y + rhs.y, z + rhs.z };
    }

    Vec3 operator-(const Vec3& rhs) const
    {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }

    Vec3 operator*(float s) const
    {
        return { x * s, y * s, z * s };
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 Normalized() const
    {
        float len = Length();
        if (len < 0.0001f) return {};
        return (*this) * (1.0f / len);
    }
};