#pragma once

#include "Core.h"

#include "Window.h"
#include "Hoowan/LayerStack.h"
#include "Hoowan/Events/Event.h"
#include "Hoowan/Events/ApplicationEvent.h"

#include "Hoowan/ImGui/ImGuiLayer.h"

#include "Hoowan/Renderer/Shader.h"
#include "Hoowan/Renderer/Buffer.h"
#include "Hoowan/Renderer/VertexArray.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}