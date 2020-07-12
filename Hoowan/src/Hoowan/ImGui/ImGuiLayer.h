#pragma once

#include "Hoowan/Core/Layer.h"

#include "Hoowan/Events/ApplicationEvent.h"
#include "Hoowan/Events/KeyEvent.h"
#include "Hoowan/Events/MouseEvent.h"

namespace Hoowan {

	class HOOWAN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}