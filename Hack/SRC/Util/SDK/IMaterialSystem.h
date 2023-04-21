#ifndef IMATERIALSYSTEM_H
#define IMATERIALSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "CKeyValues.h"

#include "../Memory/Memory.hpp"

class IMaterial
{
public:
	enum EMaterialVarFlag : int32_t
	{
		IGNOREZ = 1 << 15,
		WIREFRAME = 1 << 28
	};

	constexpr void SetMaterialVarFlag(const int32_t flag, const bool on) noexcept
	{
		Memory::Call<void>(this, 29, flag, on);
	}
};

class IMaterialSystem
{
public:
	constexpr IMaterial* CreateMaterial(const char* name, CKeyValues* kv) noexcept
	{
		return Memory::Call<IMaterial*>(this, 83, name, kv);
	}

	constexpr IMaterial* FindMaterial(const char* name) noexcept
	{
		return Memory::Call<IMaterial*>(this, 84, name, nullptr, true, nullptr);
	}
};

#endif // IMATERIALSYSTEM_H