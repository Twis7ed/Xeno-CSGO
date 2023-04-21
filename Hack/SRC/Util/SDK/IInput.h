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

	constexpr CUserCmd* GetUserCmd(const int index, const int sequenceNumber) noexcept
	{
		return Memory::Call<CUserCmd*>(this, 8, index, sequenceNumber);
	}

	[[nodiscard]] CVerifiedUserCmd* GetVerifiedUserCmd(const int sequenceNumber) const noexcept
	{
		return &pVerifiedCommands[sequenceNumber % 150];
	}
};

#endif // IINPUT_H