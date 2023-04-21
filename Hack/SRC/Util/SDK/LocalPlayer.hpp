#ifndef LOCALPLAYER_HPP
#define LOCALPLAYER_HPP
#ifdef _WIN32
#pragma once
#endif

#define DONT_INCLUDE_WINDOWS
#include "../../Core/Interfaces.hpp"

class CEntity;
namespace Globals
{
	inline CEntity* localPlayer{};

	inline void UpdateLocalPlayer() noexcept
	{
		const int32_t localPlayerIndex{ Interfaces::engine->GetLocalPlayerIndex() };
		localPlayer = Interfaces::entityList->GetEntityFromIndex(localPlayerIndex);
	}
}

#endif // LOCALPLAYER_HPP