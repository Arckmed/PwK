#pragma once
#include "pch.h"
struct Vector2 { float x, y; };
struct Vector3
{
	float x, y, z;

	Vector3() { x = -1, y = -1, z = -1; };
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) { }
	Vector3 operator + (const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator - (const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 operator * (const float& rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	Vector3 operator / (const float& rhs) const
	{
		return Vector3(x / rhs, y / rhs, z / rhs);
	}

	Vector3 operator += (Vector3& rhs)
	{
		return *this = *this + rhs;
	}

	Vector3 operator -= (Vector3& rhs)
	{
		return *this = *this - rhs;
	}

	Vector3 operator *= (float& rhs)
	{
		return *this = *this * rhs;
	}

	Vector3 operator /= (float& rhs)
	{
		return *this = *this / rhs;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Normalize() const
	{
		return *this * (1 / Length());
	}

	float Distance(const Vector3& rhs) const
	{
		return (*this - rhs).Length();
	}
};