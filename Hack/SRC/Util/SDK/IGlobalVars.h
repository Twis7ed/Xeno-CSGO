#ifndef IGLOBALVARS_H
#define IGLOBALVARS_H
#ifdef _WIN32
#pragma once
#endif

#include <cstdint>

class IGlobalVars
{
public:
	float realTime;
	int32_t frameCount;
	float absFrameTime;
	float absFrameStartTime;
	float currentTime;
	float frameTime;
	int32_t maxClients;
	int32_t tickCount;
	float intervalPerTick;
	int32_t networkProtocol;
	void* saveData;
	bool client;
	bool remoteClient;
	int32_t timestampNetworkingBase;
	int32_t timestampRandomizeWindow;
};

#endif // IGLOBALVARS_H