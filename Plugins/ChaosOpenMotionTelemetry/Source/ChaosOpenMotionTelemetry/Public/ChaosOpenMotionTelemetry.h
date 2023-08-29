/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FChaosOpenMotionTelemetryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
