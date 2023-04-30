#ifndef GUI_HPP
#define GUI_HPP
#ifdef _WIN32
#pragma once
#endif

#include <d3d9.h>

#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

namespace Gui
{
	void Init() noexcept;

	void Destroy() noexcept;

	bool InitWndClass(const char* name) noexcept;

	void DestroyWndClass() noexcept;

	bool InitWnd(const char* name) noexcept;

	void DestroyWnd() noexcept;

	bool InitDX9() noexcept;

	void DestroyDX9() noexcept;

	void InitGui(LPDIRECT3DDEVICE9 device) noexcept;

	void Render() noexcept;

	inline bool isOpen{ true };
	inline bool isSetup{ false };

	inline HWND wnd{};
	inline WNDCLASSEX wndClass{};	

	inline LPDIRECT3DDEVICE9 device{};
	inline LPDIRECT3D9 d3d9{};
}

#endif // GUI_HPP