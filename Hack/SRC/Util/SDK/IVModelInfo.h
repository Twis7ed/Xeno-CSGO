#ifndef IVMODELINFO_H
#define IVMODELINFO_H
#ifdef _WIN32
#pragma once
#endif

#include "CVector.h"

#include "../Memory/Memory.hpp"

enum EHitboxIndex : int
{
	HITBOX_INVALID = -1,
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

class CStudioBone
{
public:

};

class CStudioBoundingBox
{
public:
	int bone;
	int group;
	CVector bbMin;
	CVector bbMax;
	int hitboxNameIndex;
	CVector offsetRotation;
	float capsuleRadius;
	int unused[4];
};

class CStudioHitboxSet
{
public:
	[[nodiscard]] const char* GetName() const noexcept
	{
		return reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(this) + nameIndex);
	}

	CStudioBoundingBox* GetHitbox(const int index) noexcept
	{
		if (index < 0 || index >= numHitboxes)
			return nullptr;

		return reinterpret_cast<CStudioBoundingBox*>(reinterpret_cast<uint8_t*>(this) + hitboxIndex) + index;
	}

	int nameIndex;
	int numHitboxes;
	int hitboxIndex;
};

class CStudioHdr
{
public:
	inline CStudioBone* GetBone(int index) noexcept
	{
		if (index < 0 || index >= numBones)
			return nullptr;

		return reinterpret_cast<CStudioBone*>(reinterpret_cast<uintptr_t>(this) + boneIndex) + index;
	}

	int id;
	int version;
	int checkSum;
	char name[64];
	int length;

	CVector eyePosition;
	CVector illumPosition;
	CVector hullMin;
	CVector hullMax;
	CVector bbMin;
	CVector bbMax;

	int flag;
	int numBones;
	int boneIndex;
	int numBoneControllers;
	int boneControllerIndex;
	int numHitboxSets;
	int hitboxSetIndex;
};

class CModel
{
public:
	int32_t handle;
	char name[260];
	int32_t loadFlag;
	int32_t serverCount;
	int32_t type;
	int32_t flag;
	CVector min;
	CVector max;
	float radius;
};

class IVModelInfo
{
public:
	enum ERenderFlags : uint32_t
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

	constexpr const char* GetModelName(const CModel* model) noexcept
	{
		return Memory::Call<const char*>(this, 3, model);
	}

	constexpr CStudioHdr* GetStudioModel(const CModel* model) noexcept
	{
		return Memory::Call<CStudioHdr*>(this, 32, model);
	}
};

#endif // IVMODELINFO_H