#ifndef IENGINEVGUI_H
#define IENGINEVGUI_H
#ifdef _WIN32
#pragma once
#endif

#include "../Memory/Memory.hpp"

enum EVGuiPanel
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

class IEngineVGui
{
public:
	constexpr uintptr_t GetPanel(const int32_t type) noexcept
	{
		return Memory::Call<uintptr_t>(this, 1, type);
	}
};

#endif // IENGINEVGUI_H