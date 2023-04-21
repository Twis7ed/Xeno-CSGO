#ifndef IVPANEL_H
#define IVPANEL_H
#ifdef _WIN32
#pragma once
#endif

#include "../Memory/Memory.hpp"

class IVPanel
{
public:
	constexpr const char* GetName(const uint32_t panel) noexcept
	{
		return Memory::Call<const char*>(this, 36, panel);
	}
};

#endif // IVPANEL_H