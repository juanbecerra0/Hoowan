#include <Hoowan.h>
#include <Hoowan/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hoowan {

	class HoowanEditor : public Application {
	public:
		HoowanEditor()
			: Application("Hoowan Editor")
		{
			PushLayer(new EditorLayer());
		}

		~HoowanEditor() {

		}
	};

	Application* CreateApplication() {
		return new HoowanEditor();
	}

}