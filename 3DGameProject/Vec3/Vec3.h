#pragma once
#include <cmath>

struct Vec3
{
	float x{}, y{}, z{};

	Vec3() = default;
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	// --- Šî–{‰‰Z ---
	Vec3 operator + (const Vec3& rhs) const
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vec3 operator - (const Vec3& rhs) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vec3 operator * (float s) const
	{
		return { x * s, y * s, z * s };
	}

	Vec3& operator += (const Vec3& rhs)
	{
		x += rhs.x; y += rhs.y; z += rhs.z;
		return *this;
	}

	// --- ’·‚³ ---
	float Length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	// --- ³‹K‰» ---
	Vec3 Normalized() const
	{
		float len = Length();
		if (len < 0.0001f) return {};
		return (*this) * (1.0f / len);
	}

	// --- ŠOÏ ---
	static Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		return {
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		};
	}

	// --- XZ³‹K‰»iCamera.cpp—R—ˆj ---
	Vec3 NormalizedXZ() const
	{
		float len = std::sqrt(x * x + z * z);
		if (len < 0.0001f) return {};
		return { x / len, 0.0f, z / len };
	}
};
