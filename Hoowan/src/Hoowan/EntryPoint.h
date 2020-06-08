#pragma once

#ifdef HW_PLATFORM_WINDOWS

extern Hoowan::Application* Hoowan::CreateApplication();
	
int main(int argc, char** argv) {
	auto app = Hoowan::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif