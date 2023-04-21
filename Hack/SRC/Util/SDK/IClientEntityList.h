#ifndef ICLIENTENTITYLIST_H
#define ICLIENTENTITYLIST_H
#ifdef _WIN32
#pragma once
#endif

#include "CEntity.h"

class IClientEntityList
{
public:
	constexpr CEntity* GetEntityFromIndex(const int32_t index) noexcept
	{
		return Memory::Call<CEntity*>(this, 3, index);
	}
};

#endif // ICLIENTENTITYLIST_H