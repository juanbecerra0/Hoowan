#pragma once

#include "Core.h"

#include "Window.h"
#include "Hoowan/LayerStack.h"
#include "Hoowan/Events/Event.h"
#include "Hoowan/Events/ApplicationEvent.h"

#include "Hoowan/Core/Timestep.h"

#include "Hoowan/ImGui/ImGuiLayer.h"

namespace Hoowan {

	class HOOWAN_API Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}