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
}

#endif // GLOBALS_HPP