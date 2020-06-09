#pragma once

#ifdef HW_PLATFORM_WINDOWS

extern Hoowan::Application* Hoowan::CreateApplication();
	
int main(int argc, char** argv) {
	Hoowan::Log::Init();
	HW_CORE_WARN("Init core log!");
	HW_INFO("Init client log!");

	auto app = Hoowan::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif