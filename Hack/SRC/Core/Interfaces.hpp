#ifndef INTERFACES_HPP
#define INTERFACES_HPP
#ifdef _WIN32
#pragma once
#endif

#ifndef DONT_INCLUDE_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "../Util/SDK/IBaseClientDLL.h"
#include "../Util/SDK/IClientEntityList.h"
#include "../Util/SDK/IClientModeShared.h"
#include "../Util/SDK/IEngineTrace.h"
#include "../Util/SDK/IEngineVGui.h"
#include "../Util/SDK/IGlobalVars.h"
#include "../Util/SDK/IInputSystem.h"
#include "../Util/SDK/IMaterialSystem.h"
#include "../Util/SDK/IStudioRender.h"
#include "../Util/SDK/ISurface.h"
#include "../Util/SDK/IVDebugOverlay.h"
#include "../Util/SDK/IVEngineClient.h"
#include "../Util/SDK/IVModelInfo.h"
#include "../Util/SDK/IVPanel.h"

// https://www.youtube.com/watch?v=C0wGdwnaArA
namespace Interfaces
{
	#ifndef DONT_INCLUDE_WINDOWS
	template<typename Type>
	Type* Capture(const char* module, const char* interface) noexcept
	{
		const HINSTANCE handle{ GetModuleHandle(module) };

		if (!handle)
			return nullptr;

		using CreateInterfaceFn = Type * (__cdecl*)(const char*, int*);
		const CreateInterfaceFn createInterface{ reinterpret_cast<CreateInterfaceFn>(GetProcAddress(handle, "CreateInterface")) };

		return createInterface(interface, nullptr);
	}

	#endif

	inline IBaseClientDLL* client{};
	inline IClientEntityList* entityList{};
	inline IClientModeShared* clientMode{};
	inline IEngineTrace* engineTrace{};
	inline IEngineVGui* engineVGui{};
	inline IGlobalVars* globals{};
	inline IInputSystem* inputSystem{};
	inline IMaterialSystem* materialSystem{};
	inline IStudioRender* studioRender{};
	inline ISurface* surface{};
	inline IVDebugOverlay* debugOverlay{};
	inline IVEngineClient* engine{};
	inline IVModelInfo* modelInfo{};
	inline IVPanel* panel{};

	inline void* keyValuesSystem{};
}

#endif // INTERFACES_HPP