#ifndef MEMORY_HPP
#define MEMORY_HPP
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>
#include <functional>

namespace Memory
{
	void Init() noexcept;

	template<typename Type, typename ... Arguments>
	constexpr Type Call(void* vmt, const uint32_t index, Arguments ... args) noexcept
	{
		using Function = Type(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<Function**>(vmt))[index](vmt, args...);
	}

	constexpr void* Get(void* vmt, const uint32_t index) noexcept
	{
		return (*static_cast<void***>(vmt))[index];
	}

	inline uintptr_t RelativeToAbsolute(const uintptr_t relAddr) noexcept
	{
		return relAddr + 4 + *reinterpret_cast<std::int32_t*>(relAddr);
	}

	uint8_t* PatternScan(const char* module, const char* pattern) noexcept;
}

#endif // MEMORY_HPP