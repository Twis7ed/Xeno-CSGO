#ifndef ISPACIALQUERY_H
#define ISPACIALQUERY_H
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>

#include "CVector.h"

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/game/client/clientleafsystem.cpp#L223
enum ERenderFlags
{
	RENDER_FLAGS_DISABLE_RENDERING = 0x01,
	RENDER_FLAGS_HASCHANGED = 0x02,
	RENDER_FLAGS_ALTERNATE_SORTING = 0x04,
	RENDER_FLAGS_RENDER_WITH_VIEWMODELS = 0x08,
	RENDER_FLAGS_BLOAT_BOUNDS = 0x10,
	RENDER_FLAGS_BOUNDS_VALID = 0x20,
	RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE = 0x40,
	RENDER_FLAGS_IS_SPRITE = 0x80,
	RENDER_FLAGS_FORCE_OPAQUE_PASS = 0x100
};

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/game/client/clientleafsystem.cpp#L240
class IClientRenderable;
class CRenderableInfo
{
public:
	IClientRenderable* renderable;
	void* alphaProperty;
	int32_t enumCount;
	int32_t renderFrame;
	uint16_t firstShadow;
	uint16_t leafList;
	int16_t area;
	int16_t flag;
	int16_t flag2;
	CVector bloatedAbsMin;
	CVector bloatedAbsMax;
	CVector min;
	CVector max;
	std::byte pad0[0x4];
};

class ISpacialQuery
{
public:

};

#endif // ISPACIALQUERY_H