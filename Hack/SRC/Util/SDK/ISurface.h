#ifndef ISURFACE_H
#define ISURFACE_H
#ifdef _WIN32
#pragma once
#endif

#include "../Memory/Memory.hpp"

enum EFontDrawType : int32_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE
};

enum EFontFlag
{
	FONT_FLAG_NONE,
	FONT_FLAG_ITALIC = 0x001,
	FONT_FLAG_UNDERLINE = 0x002,
	FONT_FLAG_STRIKEOUT = 0x004,
	FONT_FLAG_SYMBOL = 0x008,
	FONT_FLAG_ANTIALIAS = 0x010,
	FONT_FLAG_GAUSSIANBLUR = 0x020,
	FONT_FLAG_ROTARY = 0x040,
	FONT_FLAG_DROPSHADOW = 0x080,
	FONT_FLAG_ADDITIVE = 0x100,
	FONT_FLAG_OUTLINE = 0x200,
	FONT_FLAG_CUSTOM = 0x400,
	FONT_FLAG_BITMAP = 0x800
};

class ISurface
{
	constexpr void DrawSetColor(const int r, const int g, const int b, const int a = 255) noexcept
	{
		Memory::Call<void>(this, 15, r, g, b, a);
	}

	constexpr void DrawFilledRect(const int x, const  int y, const int xx, const int yy) noexcept
	{
		Memory::Call<void>(this, 16, x, y, xx, yy);
	}

	constexpr void DrawOutlineRect(const int x, const  int y, const int xx, const int yy) noexcept
	{
		Memory::Call<void>(this, 18, x, y, xx, yy);
	}
};

#endif // ISURFACE