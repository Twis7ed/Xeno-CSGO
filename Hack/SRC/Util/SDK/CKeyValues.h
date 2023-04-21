#ifndef CKEYVALUES_H
#define CKEYVALUES_H
#ifdef _WIN32
#pragma once
#endif

#include "../Memory/Memory.hpp"

// https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/tier1/keyvalues.cpp#L3652
class CKeyValues
{
public:
	static CKeyValues* FromString(const char* name, const char* value) noexcept
	{
		static uintptr_t functionAddress{ Memory::RelativeToAbsolute(reinterpret_cast<uintptr_t>(Memory::PatternScan("client.dll", "E8 ? ? ? ? 8B 0D ? ? ? ? 83 C4 04 8B F8 8B 11") + 1)) };
		CKeyValues* kv;

		__asm
		{
			push 0
			mov edx, value
			mov ecx, name
			call functionAddress
			add esp, 4
			mov kv, eax
		}

		return kv;
	}
};

#endif // CKEYVALUES_H