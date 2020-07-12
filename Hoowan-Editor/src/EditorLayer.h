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
		OrthographicCameraController m_CameraController;
		Ref<FrameBuffer> m_FrameBuffer;

		LevelParser m_LevelParser;
	};

}