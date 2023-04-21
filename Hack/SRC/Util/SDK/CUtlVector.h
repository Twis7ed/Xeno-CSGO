#ifndef CUTLVECTOR_H
#define CUTLVECTOR_H
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>

template <typename Type>
class CUtlVector
{
public:
	constexpr Type& operator[](size_t index) noexcept
	{
		return memory[index];
	}

	constexpr const Type& operator[](size_t index) const noexcept
	{
		return memory[index];
	}

	Type* memory;
	int32_t allocCount;
	int32_t growSize;
	int32_t size;
	Type* element;
};

#endif // CUTLVECTOR_H