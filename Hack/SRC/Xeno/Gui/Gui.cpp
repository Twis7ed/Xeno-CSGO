#define DONT_INCLUDE_SDK
#include "../../Core/Hooks/Hooks.hpp"

#include "../Config/Config.hpp"

void Gui::Init() noexcept
{
	InitWndClass("class01");

	InitWnd("Window");

	InitDX9();

	DestroyWnd();

	DestroyWndClass();
}

void Gui::Destroy() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	DestroyDX9();
}

bool Gui::InitWndClass(const char* name) noexcept
{
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = DefWindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hIcon = nullptr;
	wndClass.hCursor = nullptr;
	wndClass.hbrBackground = nullptr;
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = name;
	wndClass.hIconSm = nullptr;

	if (RegisterClassEx(&wndClass))
		return false;

	return true;
}

void Gui::DestroyWndClass() noexcept
{
	UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
}

bool Gui::InitWnd(const char* name) noexcept
{
	wnd = CreateWindow(wndClass.lpszClassName, name, WS_OVERLAPPED, 0, 0, 100, 100, nullptr, nullptr, wndClass.hInstance, nullptr);
	if (!wnd)
		return false;

	return true;
}

void Gui::DestroyWnd() noexcept
{
	if (wnd)
		DestroyWindow(wnd);
}

bool Gui::InitDX9() noexcept
{
	const HMODULE handle{ GetModuleHandle("d3d9.dll") };
	if (!handle)
		return false;

	using CreateFn = LPDIRECT3D9(__stdcall*)(UINT);
	const auto create{ reinterpret_cast<CreateFn>(GetProcAddress(handle, "Direct3DCreate9")) };
	if (!create)
		return false;

	d3d9 = create(D3D_SDK_VERSION);
	if (!d3d9)
		return false;

	D3DPRESENT_PARAMETERS params{};
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = wnd;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	if (d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, wnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0)
		return false;

	return true;
}

void Gui::DestroyDX9() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d9)
	{
		d3d9->Release();
		d3d9 = nullptr;
	}
}

void Gui::InitGui(const LPDIRECT3DDEVICE9 device) noexcept
{
	auto params{ D3DDEVICE_CREATION_PARAMETERS{} };
	device->GetCreationParameters(&params);

	wnd = params.hFocusWindow;
	Hooks::WndProcOriginal = SetWindowLongPtr(wnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::WndProc));

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(wnd);
	ImGui_ImplDX9_Init(device);

	isSetup = true;
}

void Gui::Render() noexcept
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Xeno", &isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize(ImVec2(560.f, 420.f));

	if (ImGui::BeginTabBar("Tabs"))
	{
		if (ImGui::BeginTabItem("Aimbot"))
		{
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Visuals"))
		{
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Checkbox("Bhop", &misc.mvmnt.bunnyhop);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Config"))
		{
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}