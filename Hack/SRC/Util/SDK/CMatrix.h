#ifndef CMATRIX_H
#define CMATRIX_H
#ifdef _WIN32
#pragma once
#endif

#include "CVector.h"

class CMatrix3x4
{
public:
	constexpr float* operator[](const size_t index) noexcept
	{
		return data[index];
	}

	[[nodiscard]] constexpr CVector Origin() const noexcept
	{
		return { data[0][3], data[1][3], data[2][3] };
	}

	float data[3][4];
};

class CMatrix4x4
{
public:
	float data[4][4];
};

#endif // CMATRIX_H