#include "Sandbox2D.h"
#include "Hoowan/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

//#include <Hoowan\Renderer\Renderer2D.h>

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

	// Camera
	m_CameraController.OnUpdate(ts);

	// Clear  buffer
	Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hoowan::RenderCommand::Clear();

	// Begin scene
	Hoowan::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//Hoowan::Renderer2D::DrawQuad({ 0.0f, -0.5f }, 0.0f, { 2.0f, 1.0f, 1.0f}, { 0.8f, 0.2f, 0.3f, 1.0f });
	//Hoowan::Renderer2D::DrawQuad({ 1.0f, 0.5f }, 45.0f, { 1.0f, 2.0f, 1.0f }, { 0.4f, 0.9f, 0.3f, 1.0f });

	for (int x = -5; x < 5; x++)
	{
		for (int y = -5; y < 5; y++)
		{
			Hoowan::Renderer2D::DrawQuad({ (float)x, (float)y, 0.1f }, 0.0f, { 1.0f, 1.0f, 1.0f }, m_Texture);
		}
	}

	Hoowan::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
