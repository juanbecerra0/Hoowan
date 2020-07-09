#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	HW_PROFILE_FUNCTION();

	m_Texture = Hoowan::Texture2D::Create("assets/textures/test.png");
}

void Sandbox2D::OnDetach()
{
	HW_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Hoowan::Timestep ts)
{
	HW_PROFILE_FUNCTION();

	// Camera Input/VP update
	m_CameraController.OnUpdate(ts);

	// Reset statistics
	Hoowan::Renderer2D::ResetStats();

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

		const int dimensions = 316;
		const float scale = 0.8f;

		static float rotation = 0.0f;
		rotation += 45 * ts;

		// Draw static quads
		for (int x = -(dimensions / 2); x < (dimensions / 2); x++)
		{
			for (int y = -(dimensions / 2); y < (dimensions / 2); y++)
			{
				if ((x + y) % 2 == 0)
					Hoowan::Renderer2D::DrawStaticQuad({ (float)x, (float)y, 0.1f }, { scale, scale }, m_Texture);
				else
					Hoowan::Renderer2D::DrawStaticQuad({ (float)x, (float)y, 0.1f }, { scale, scale }, m_Color);
			}
		}

		/*
		// Draw rotating quads
		for (int x = -(dimensions / 2); x < (dimensions / 2); x++)
		{
			for (int y = -(dimensions / 2); y < (dimensions / 2); y++)
			{
				if ((x + y) % 2 == 0)
					Hoowan::Renderer2D::DrawRotatedQuad({ (float)x, (float)y, 0.1f }, (x + y) * 15.0f + rotation, { scale, scale }, m_Texture);
				else
					Hoowan::Renderer2D::DrawRotatedQuad({ (float)x, (float)y, 0.1f }, (x + y) * 15.0f + rotation, { scale, scale }, m_Color);
			}
		}
		*/

		// End scene
		Hoowan::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HW_PROFILE_FUNCTION();

	// Stats
	auto stats = Hoowan::Renderer2D::GetStats();

	ImGui::Begin("Renderer2D Stats");
	ImGui::Text("Draw Calls: %d", stats.GetDrawCallCount());
	ImGui::Text("Quads: %d", stats.GetQuadCount());
	ImGui::Text("Triangles: %d", stats.GetTriangleCount());
	ImGui::Text("Vertices: %d", stats.GetVertexCount());
	ImGui::Text("Indices: %d", stats.GetIndexCount());
	ImGui::End();

	// Color selection
	ImGui::Begin("Color Selector");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();

}

void Sandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
