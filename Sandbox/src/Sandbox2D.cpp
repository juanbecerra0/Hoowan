#include "Sandbox2D.h"
#include "Hoowan/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Hoowan::Texture2D::Create("assets/textures/test.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hoowan::Timestep ts)
{
	HW_PROFILE_FUNCTION();

	{
		HW_PROFILE_SCOPE("CameraController::OnUpdate");

		// Camera Input/VP update
		m_CameraController.OnUpdate(ts);
	}

	{
		HW_PROFILE_SCOPE("ClearBuffer::OnUpdate");

		// Clear frame buffer
		Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hoowan::RenderCommand::Clear();
	}

	{
		HW_PROFILE_SCOPE("RenderDrawScene::OnUpdate");

		// Begin scene
		Hoowan::Renderer2D::BeginScene(m_CameraController.GetCamera());

		// Draw 100 quads
		for (int x = -5; x < 5; x++)
		{
			for (int y = -5; y < 5; y++)
			{
				if ((x + y) % 2 == 0)
					Hoowan::Renderer2D::DrawQuad({ (float)x, (float)y, 0.1f }, 0.0f, { 1.0f, 1.0f, 1.0f }, m_Texture);
				else
					Hoowan::Renderer2D::DrawQuad({ (float)x, (float)y, 0.1f }, 0.0f, { 1.0f, 1.0f, 1.0f }, m_Color);
			}
		}

		// End scene
		Hoowan::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HW_PROFILE_FUNCTION();

	// Color selection
	ImGui::Begin("Color Selector");

	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));

	ImGui::End();

}

void Sandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
