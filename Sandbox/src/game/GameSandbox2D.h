#pragma once

#include "Hoowan.h"

#include "LevelParser.h"
#include "Levels.h"

class GameSandbox2D : public Hoowan::Layer
{
public:
	GameSandbox2D();
	virtual ~GameSandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hoowan::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hoowan::Event& e) override;

private:
	Hoowan::Ref<Hoowan::FrameBuffer> m_FrameBuffer;

	Hoowan::OrthographicCameraController m_CameraController;

	LevelParser m_LevelParser;
};