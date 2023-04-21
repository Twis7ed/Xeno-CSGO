#ifndef IBASECLIENTDLL_H
#define IBASECLIENTDLL_H
#ifdef _WIN32
#pragma once
#endif

#include "CClientClass.h"

#include "../Memory/Memory.hpp"

class IBaseClientDLL
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return Memory::Call<CClientClass*>(this, 8);
	}
};

#endif // IBASECLIENTDLL_H