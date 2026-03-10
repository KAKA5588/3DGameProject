#pragma once
#include <cmath>
#include "DxLib.h"

struct Vec3
{
    float x{}, y{}, z{};

    // ===== コンストラクタ =====

    Vec3() = default;

    Vec3(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) {}

    // DxLibのVECTORから変換
    Vec3(const VECTOR& v)
        : x(v.x), y(v.y), z(v.z) {}

    // Vec3 → VECTOR 変換
    operator VECTOR() const
    {
        return VGet(x, y, z);
    }

    // ===== 演算子 =====

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

    Vec3& operator*=(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    //  数学関数 

    float Length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float LengthSq() const
    {
        return x * x + y * y + z * z;
    }

    Vec3 Normalized() const
    {
        float len = Length();
        if (len < 0.0001f) return {};
        return (*this) * (1.0f / len);
    }

    float Dot(const Vec3& rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    Vec3 Cross(const Vec3& rhs) const
    {
        return {
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        };
    }
};