#ifndef IINPUT_H
#define IINPUT_H
#ifdef _WIN32
#pragma once
#endif

#include "CUserCmd.h"

#include "../Memory/Memory.hpp"

class IInput
{
public:
	constexpr CUserCmd* GetUserCmd(const int slot, const int sequenceNumber) noexcept
	{
		return Memory::Call<CUserCmd*>(this, 8, slot, sequenceNumber);
	}

	[[nodiscard]] CVerifiedUserCmd* GetVerifiedUserCmd(const int sequenceNumber) const noexcept
	{
		return &pVerifiedCommands[sequenceNumber % 150];
	}

	std::byte pad0[0xC];
	bool trackIrAvailable;
	bool mouseInitialized;
	bool mouseActive;
	std::byte pad1[0x9A];
	bool cameraInThirdPerson;
	std::byte pad2[0x2];
	CVector cameraOffset;
	std::byte pad3[0x38];
	CUserCmd* pCommands;
	CVerifiedUserCmd* pVerifiedCommands;
};

#endif // IINPUT_H