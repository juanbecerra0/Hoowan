#pragma once

#include "Hoowan.h"

class Sandbox2D : public Hoowan::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hoowan::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hoowan::Event& e) override;

private:
	Hoowan::Ref<Hoowan::Shader> m_Shader;

	Hoowan::Ref<Hoowan::VertexArray> m_VertexArray;
	Hoowan::OrthographicCameraController m_CameraController;

	glm::vec4 m_Color = { 0.2f, 0.3f, 0.8f, 1.0f };
	Hoowan::Ref<Hoowan::Texture2D> m_Texture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};