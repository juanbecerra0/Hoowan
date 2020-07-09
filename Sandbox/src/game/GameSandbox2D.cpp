#include "GameSandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

GameSandbox2D::GameSandbox2D()
	: Layer("GameSandbox2D"), m_CameraController(1920.0f / 1080.0f, true)
{

}

void GameSandbox2D::OnAttach()
{
	HW_PROFILE_FUNCTION();
}

void GameSandbox2D::OnDetach()
{
	HW_PROFILE_FUNCTION();
}

void GameSandbox2D::OnUpdate(Hoowan::Timestep ts)
{
	HW_PROFILE_FUNCTION();

	// Camera Input/VP update
	m_CameraController.OnUpdate(ts);

	// Reset statistics
	Hoowan::Renderer2D::ResetStats();
	Hoowan::Renderer2D::StatsBeginFrame();

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


		// End scene
		Hoowan::Renderer2D::EndScene();

		Hoowan::Renderer2D::StatsEndFrame();
	}
}

void GameSandbox2D::OnImGuiRender()
{
	HW_PROFILE_FUNCTION();

	// Stats
	auto stats = Hoowan::Renderer2D::GetStats();
	float averageRenderTime = stats.TotalFrameRenderTime / stats.FrameRenderTimes.size() * 100.0f; // nb: wont be accurate until we have gathered at least stats.FrameRenderTime().size() results
	float averageFPS = (1.0f / averageRenderTime);

	ImGui::Begin("Renderer2D Stats");
	ImGui::Text("Render time: %8.5f", averageRenderTime);
	ImGui::Text("Render framerate: %5.0f", averageFPS);
	ImGui::Text("");
	ImGui::Text("Draw Calls: %d", stats.GetDrawCallCount());
	ImGui::Text("Quads: %d", stats.GetQuadCount());
	ImGui::Text("Triangles: %d", stats.GetTriangleCount());
	ImGui::Text("Vertices: %d", stats.GetVertexCount());
	ImGui::Text("Indices: %d", stats.GetIndexCount());
	ImGui::End();

}

void GameSandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
