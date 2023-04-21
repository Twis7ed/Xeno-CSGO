#include <intrin.h>
#include <algorithm>

#include "Hooks.hpp"

#include "MinHook/minhook.h"

#include "../../Util/Sdk/LocalPlayer.hpp"

void Hooks::Init() noexcept
{
	MH_Initialize();

	MH_CreateHook(Memory::Get(Gui::device, 42), &EndScene, reinterpret_cast<void**>(&EndSceneOriginal));

	MH_CreateHook(Memory::Get(Gui::device, 16), &Reset, reinterpret_cast<void**>(&ResetOriginal));

	MH_EnableHook(nullptr);

	Gui::DestroyDirectX();
}

void Hooks::Destroy() noexcept
{
	MH_DisableHook(nullptr);
	MH_RemoveHook(nullptr);
	MH_Uninitialize();
	SetWindowLongPtr(Gui::wnd, GWLP_WNDPROC, WndProcOriginal);
}

DWORD WINAPI Unload(LPVOID) noexcept
{
	Hooks::Destroy();
	Gui::Destroy();

	Interfaces::inputSystem->EnableInput(true);

	HMODULE hInst;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<LPCSTR>(Unload), &hInst);
	FreeLibraryAndExitThread(hInst, EXIT_SUCCESS);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall Hooks::WndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) noexcept
{
	if (uMsg == WM_KEYDOWN && wParam == VK_INSERT)
		Gui::isOpen = !Gui::isOpen;

	Interfaces::inputSystem->EnableInput(!Gui::isOpen);

	if (Gui::isOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1l;

	if (uMsg == WM_KEYDOWN && wParam == VK_END)
		if (const HANDLE hThread{ CreateThread(nullptr, NULL, Unload, nullptr, NULL, nullptr) })
			CloseHandle(hThread);

	return CallWindowProc(reinterpret_cast<WNDPROC>(WndProcOriginal), hWnd, uMsg, wParam, lParam);
}

long __stdcall Hooks::EndScene(IDirect3DDevice9* device) noexcept
{
	if (static const void* address{ _ReturnAddress() }; address == _ReturnAddress())
		return EndSceneOriginal(device, device);

	if (!Gui::isSetup)
		Gui::InitGui(device);

	if (Gui::isOpen)
		Gui::Render();

	return EndSceneOriginal(device, device);
}

HRESULT __stdcall Hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	return ResetOriginal(device, device, params);
}