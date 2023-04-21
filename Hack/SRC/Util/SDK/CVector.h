#ifndef CVECTOR_H
#define CVECTOR_H
#ifdef _WIN32
#pragma once
#endif

#include <cmath>
#include <cstdint>
#include <numbers>

class CVector
{
public:
	constexpr CVector operator+(const CVector& other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator-(const CVector& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	constexpr CVector operator*(const CVector& other) const noexcept
	{
		return { x * other.x, y * other.y, z * other.z };
	}

	constexpr CVector operator/(const CVector& other) const noexcept
	{
		return { x / other.x, y / other.y, z / other.z };
	}

	[[nodiscard]] constexpr CVector Scale(const float factor) const noexcept
	{
		return { x * factor, y * factor, z * factor };
	}

	[[nodiscard]] CVector ToAngle() const noexcept
	{
		return {
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f
		};
	}

	void Normalize() noexcept
	{
		x = std::isfinite(x) ? std::remainderf(x, 360.0f) : 0.0f;
		y = std::isfinite(y) ? std::remainderf(y, 360.0f) : 0.0f;
		z = 0.0f;
	}

	float x{}, y{}, z{};
};

__declspec(align(16)) class CVectorAligned : public CVector
{
public:
	constexpr CVectorAligned operator-(const CVectorAligned& other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	float w{};
};

#endif // CVECTOR_Hs