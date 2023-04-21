#ifndef IVENGINECLIENT_H
#define IVENGINECLIENT_H
#ifdef _WIN32
#pragma once
#endif

#include "CVector.h"
#include "CMatrix.h"
#include "ISpacialQuery.h"

#include "../Memory/Memory.hpp"

class IVEngineClient
{
public:
	constexpr void GetScreenSize(int32_t& width, int32_t height) noexcept
	{
		Memory::Call<void>(this, 5, std::ref(width), std::ref(height));
	}

	constexpr int32_t GetLocalPlayerIndex() noexcept
	{
		return Memory::Call<int32_t>(this, 12);
	}

	constexpr void SetViewAngles(const CVector& viewAngles) noexcept
	{
		Memory::Call<void, const CVector&>(this, 19, viewAngles);
	}

	constexpr bool IsInGame() noexcept
	{
		return Memory::Call<bool>(this, 26);
	}
	constexpr const CMatrix4x4& WorldToScreenMatrix() noexcept
	{
		return Memory::Call<const CMatrix4x4&>(this, 37);
	}

	constexpr ISpacialQuery* GetBSPTreeQuery() noexcept
	{
		return Memory::Call<ISpacialQuery*>(this, 43);
	}
};

#endif // IVENGINECLIENT_H