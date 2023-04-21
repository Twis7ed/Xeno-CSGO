#include <vector>

#include "../../Core/Interfaces.hpp"
using namespace Interfaces;

void Memory::Init() noexcept
{
	client = Capture<IBaseClientDLL>("client.dll", "VClient018");
	entityList = Capture<IClientEntityList>("client.dll", "VClientEntityList003");
	clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	engineTrace = Capture<IEngineTrace>("engine.dll", "EngineTraceClient004");
	engineVGui = Capture<IEngineVGui>("engine.dll", "VEngineVGui001");
	globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	materialSystem = Capture<IMaterialSystem>("materialsystem.dll", "VMaterialSystem080");
	inputSystem = Capture<IInputSystem>("inputsystem.dll", "InputSystemVersion001");
	studioRender = Capture<IStudioRender>("studiorender.dll", "VStudioRender026");
	surface = Capture<ISurface>("vguimatsurface.dll", "VGUI_Surface031");
	debugOverlay = Capture<IVDebugOverlay>("engine.dll", "VDebugOverlay004");
	engine = Capture<IVEngineClient>("engine.dll", "VEngineClient014");
	modelInfo = Capture<IVModelInfo>("engine.dll", "VModelInfoClient004");
	panel = Capture<IVPanel>("vgui2.dll", "VGUI_Panel009");
}

uint8_t* Memory::PatternScan(const char* module, const char* pattern) noexcept
{
	static auto patternToByte = [](const char* pattern) noexcept -> const std::vector<int32_t>
	{
		auto bytes{ std::vector<int32_t>{} };
		const auto start{ const_cast<char*>(pattern) };
		const char* end{ const_cast<char*>(pattern) + std::strlen(pattern) };

		for (auto current{ start }; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;

				bytes.push_back(-1);
			}
			else
				bytes.push_back(std::strtoul(current, &current, 16));
		}

		return bytes;
	};

	const HINSTANCE handle{ GetModuleHandle(module) };
	if (!handle)
		return nullptr;

	const auto dosHeader{ reinterpret_cast<PIMAGE_DOS_HEADER>(handle) };
	const auto ntHeaders{ reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(handle) + dosHeader->e_lfanew) };

	const uintptr_t size{ ntHeaders->OptionalHeader.SizeOfImage };
	const std::vector bytes{ patternToByte(pattern) };
	const auto scanBytes{ reinterpret_cast<uint8_t*>(handle) };

	const size_t s{ bytes.size() };
	const int32_t* d{ bytes.data() };

	for (size_t i{ 0ul }; i < size - s; ++i)
	{
		bool found{ true };

		for (size_t j{ 0ul }; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
			return &scanBytes[i];
	}

	return nullptr;
}
