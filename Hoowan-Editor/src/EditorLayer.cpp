#include "EditorLayer.h"

#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Hoowan
{

	EditorLayer::EditorLayer()
		:	Layer("EditorLayer"), m_CameraController(1920.0f / 1080.0f, true),
			m_LevelParser(TestLevel2)
	{

	}

	void EditorLayer::OnAttach()
	{
		HW_PROFILE_FUNCTION();

		FrameBufferSpecs specs{ 1920, 1080 };
		m_FrameBuffer = FrameBuffer::Create(specs);
	}

	void EditorLayer::OnDetach()
	{
		HW_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Hoowan::Timestep ts)
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
			m_FrameBuffer->Bind();
			Hoowan::RenderCommand::SetClearColor({ 0.529f, 0.808f, 0.922f, 1 });
			Hoowan::RenderCommand::Clear();
		}

		{
			HW_PROFILE_SCOPE("RenderDrawScene::OnUpdate");

			// Begin scene
			Hoowan::Renderer2D::BeginScene(m_CameraController.GetCamera());

			// Render entire scene
			m_LevelParser.RenderLevel();

			// End scene
			Hoowan::Renderer2D::EndScene();
			m_FrameBuffer->Unbind();

			Hoowan::Renderer2D::StatsEndFrame();
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		HW_PROFILE_FUNCTION();

		static bool opt_fullscreen_persistant = true;
		static bool* p_open = new bool;
		*p_open = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Application"))
			{
				if (ImGui::MenuItem("Exit")) Hoowan::Application::Get().CloseApplication();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// Stats
		auto stats = Hoowan::Renderer2D::GetStats();
		float averageRenderTime = stats.TotalFrameRenderTime / stats.FrameRenderTimes.size() * 100.0f;
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

		// Scene viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Scene Viewport");
		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		// Check if viewport has been resized
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
		}
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Hoowan::Event& e)
	{
		m_CameraController.OnEvent(e);
	}


}