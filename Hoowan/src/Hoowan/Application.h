#pragma once

#include "Core.h"

#include "Window.h"
#include "Hoowan/LayerStack.h"
#include "Hoowan/Events/Event.h"
#include "Hoowan/Events/ApplicationEvent.h"

namespace Hoowan {

	class HOOWAN_API Application {
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}