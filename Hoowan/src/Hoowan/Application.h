#pragma once
#include "hwpch.h"

#include "Core.h"
#include "Events/Event.h"

#include "Window.h"

namespace Hoowan {

	class HOOWAN_API Application {
	public:
		Application();
		~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}