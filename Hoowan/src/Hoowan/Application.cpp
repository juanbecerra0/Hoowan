#include "Application.h"

#include "Hoowan/Events/ApplicationEvent.h"
#include "Hoowan/Log.h"

namespace Hoowan {

	Application::Application() {

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

		while (true);
	}

}