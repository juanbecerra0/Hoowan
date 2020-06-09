#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hoowan {

	class HOOWAN_API Application {
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}