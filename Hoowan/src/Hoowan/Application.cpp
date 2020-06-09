#include "hwpch.h"

#include "Application.h"

#include "Hoowan/Events/ApplicationEvent.h"
#include "Hoowan/Log.h"

#include <GLFW/glfw3.h>

namespace Hoowan {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HW_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HW_TRACE(e);
		}

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}