#include <intrin.h>
#include <algorithm>

#include "Hooks.hpp"

#include "MinHook/minhook.h"

#include "../Globals.hpp"
#include "../../Xeno/Features/Misc/Misc.hpp"

void Hooks::Init() noexcept
{
	MH_Initialize();

	MH_CreateHook(Memory::Get(Gui::device, 42), &EndScene, reinterpret_cast<void**>(&EndSceneOriginal));

	MH_CreateHook(Memory::Get(Gui::device, 16), &Reset, reinterpret_cast<void**>(&ResetOriginal));

	MH_CreateHook(Memory::Get(Interfaces::client, 22), &CreateMoveProxy, reinterpret_cast<void**>(&CreateMoveOriginal));

	MH_EnableHook(nullptr);

	Gui::DestroyDX9();
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

static bool __stdcall CreateMove(float sampleTime, CUserCmd* cmd, const bool& sendPacket) noexcept
{
	Globals::localPlayer = Interfaces::entityList->GetEntityFromIndex(Interfaces::engine->GetLocalPlayerIndex());

	auto oldViewAngles{ cmd->viewAngles };
	auto oldForwardMove{ cmd->forwardMove };
	auto oldSideMove{ cmd->sideMove };

	Features::Bunnyhop(cmd);

	if (sendPacket)
		Globals::angles = cmd->viewAngles;

	Globals::sendPacket = sendPacket;

	cmd->forwardMove = std::clamp(cmd->forwardMove, -450.f, 450.f);
	cmd->sideMove = std::clamp(cmd->sideMove, -450.f, 450.f);
	cmd->upMove = std::clamp(cmd->upMove, -320.f, 320.f);

	cmd->viewAngles.Normalize();
	cmd->viewAngles.x = std::clamp(cmd->viewAngles.x, -89.f, 89.f);
	cmd->viewAngles.y = std::clamp(cmd->viewAngles.y, -180.f, 180.f);
	cmd->viewAngles.x = 0.f;

	Globals::realAngles = cmd->viewAngles;

	return false;
}

static void __stdcall CreateMoveCallback(const int sequenceNumber, const float sampleTime, const bool isActive, const bool& sendPacket) noexcept
{
	Hooks::CreateMoveOriginal(sequenceNumber, sampleTime, isActive);

	const CUserCmd* cmd{ Interfaces::input->GetUserCmd(0, sequenceNumber) };
	if (!cmd || cmd->commandNumber)
		return;
	
	CVerifiedUserCmd* verifiedCmd{ Interfaces::input->GetVerifiedUserCmd(sequenceNumber) };
	if (!verifiedCmd)
		return;
	
	// CreateMove(sampleTime, cmd, sendPacket);

	verifiedCmd->cmd = *cmd;
	verifiedCmd->crc = cmd->GetChecksum();
}

__declspec(naked) void __stdcall Hooks::CreateMoveProxy(int sequenceNumber, float sampleTime, bool isActive) noexcept
{
	__asm
	{
		push ebp
		mov ebp, esp
		push ebx
		push esp
		push dword ptr[isActive]
		push dword ptr[sampleTime]
		push dword ptr[sequenceNumber]
		call CreateMoveCallback
		pop ebx
		pop ebp
		retn 0Ch
	}
}
