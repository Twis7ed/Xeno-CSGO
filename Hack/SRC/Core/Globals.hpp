#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#ifdef _WIN32
#pragma once
#endif

#define DONT_INCLUDE_WINDOWS
#include "Interfaces.hpp"

namespace Globals
{
	inline CEntity* localPlayer{};
	inline CVector angles{};
	inline CVector realAngles{};
	inline bool sendPacket{ true };
}

#endif // GLOBALS_HPP