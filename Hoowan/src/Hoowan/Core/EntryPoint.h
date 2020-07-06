#pragma once
#include "hwpch.h"

#ifdef HW_PLATFORM_WINDOWS

extern Hoowan::Application* Hoowan::CreateApplication();
	
int main(int argc, char** argv) {
	Hoowan::Log::Init();

	// Start app
	HW_PROFILE_BEGIN_SESSION("Startup", "HoowanProfile-Startup.json");
	auto app = Hoowan::CreateApplication();
	HW_PROFILE_END_SESSION();

	// Begin runtime
	HW_PROFILE_BEGIN_SESSION("Runtime", "HoowanProfile-Runtime.json");
	app->Run();
	HW_PROFILE_END_SESSION();

	// Exit app
	HW_PROFILE_BEGIN_SESSION("Shutdown", "HoowanProfile-Shutdown.json");
	delete app;
	HW_PROFILE_END_SESSION();

	return 0;
}

#endif