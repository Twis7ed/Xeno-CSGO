#ifndef CCOLOR_H
#define CCOLOR_H
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>

class CColor
{
public:
	constexpr CColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255) :
		r(r), g(g), b(b), a(a) {}

	static CColor Red() { return { 255, 0, 0 }; }
	static CColor Green() { return{ 0, 255, 0 }; }
	static CColor Blue() { return{ 0, 0, 255 }; }
	static CColor Black() { return{ 0, 0, 0 }; }
	static CColor White() { return{ 255, 255, 255 }; }

	uint8_t r{}, g{}, b{}, a{};
};

#endif // CCOLOR_H