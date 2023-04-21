#ifndef HOOKS_HPP
#define HOOKS_HPP
#ifdef _WIN32
#pragma once
#endif

#ifndef DONT_INCLUDE_SDK
#include "../Interfaces.hpp"
#endif

#include "../../Xeon/Gui/Gui.hpp"

namespace Hooks
{
	void Init() noexcept;

	void Destroy() noexcept;

	inline LONG_PTR WndProcOriginal{};
	LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*) noexcept;
	inline EndSceneFn EndSceneOriginal{};
	long __stdcall EndScene(IDirect3DDevice9* device) noexcept;

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*) noexcept;
	inline ResetFn ResetOriginal{};
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept;
}

#endif // HOOKS_HPP