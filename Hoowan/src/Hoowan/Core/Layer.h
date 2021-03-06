#pragma once

#include "Hoowan/Core/Core.h"
#include "Hoowan/Core/Timestep.h"
#include "Hoowan/Events/Event.h"

namespace Hoowan {

	class HOOWAN_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
