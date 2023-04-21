#ifndef HASH_HPP
#define HASH_HPP
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>
#include <string_view>

namespace Hash
{
	constexpr uint32_t base{ 0x811C9DC5 };
	constexpr uint32_t prime{ 0x1000193 };

	consteval uint32_t CompileTime(const char* data, const uint32_t value = base) noexcept
	{
		return (data[0] == '\0') ? value : CompileTime(&data[1], (value ^ static_cast<uint32_t>(data[0])) * prime);
	}

	inline uint32_t RunTime(const std::string_view data) noexcept
	{
		uint32_t hashed{ base };

		for (const char& character : data)
		{
			hashed ^= character;
			hashed *= prime;
		}

		return hashed;
	}
}

#endif // HASH_HPP