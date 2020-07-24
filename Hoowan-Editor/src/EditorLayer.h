#pragma once

#include "Hoowan.h"

#include "game/LevelParser.h"
#include "game/Levels.h"

namespace Hoowan
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		Ref<Scene> m_Scene;
		Entity m_SquareEnt;

		OrthographicCameraController m_CameraController;
		Ref<FrameBuffer> m_FrameBuffer;

		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		LevelParser m_LevelParser;
	};

}