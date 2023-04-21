#include <thread>

#include "Core/Hooks/Hooks.hpp"

DWORD WINAPI Init(LPVOID) noexcept
{
	Memory::Init();
	Netvars::Init();
	Gui::Init();
	Hooks::Init();

	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(const HINSTANCE hInstDLL, const DWORD fdwReason, LPVOID) noexcept
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstDLL);
		if (const HANDLE hThread{ CreateThread(nullptr, NULL, Init, nullptr, NULL, nullptr) })
			CloseHandle(hThread);
	}

	return TRUE;
}