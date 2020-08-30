#include "EditorLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/compatibility.hpp>

namespace Hoowan
{

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_CameraController(1920.0f / 1080.0f, true),
		m_ViewportSize({ 1920.0f, 1080.0f }), m_Scene(CreateRef<Scene>()),
		m_Player(m_Scene, glm::vec2(6.3f, 2.0f))
	{
		
	}

	void EditorLayer::OnAttach()
	{
		HW_PROFILE_FUNCTION();

		FrameBufferSpecs specs{ 1920, 1080 };
		m_FrameBuffer = FrameBuffer::Create(specs);

		m_LevelParser = { TestLevel2, m_Scene };

		// Add a square entity to the scene
		m_SquareEnt = m_Scene->CreateEntity("Square");
		m_SquareEnt.GetComponent<TransformComponent>().GetTransform() =
			glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, -1.0f, 0.0f));

		m_SquareEnt.AddComponent<SpriteRendererColorComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_SquareEnt.AddComponent<Collider2DDynamicComponent>(m_SquareEnt.GetComponent<TransformComponent>().Transform);

		// Add a camera component to the scene
		m_CameraEntity = m_Scene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();
		m_CameraEntity.GetComponent<CameraComponent>().IsPrimary = true;

		// Add a scriptable components

		
		class CameraController : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				//std::cout << "CreateCameraEnt" << std::endl;
			}

			void OnDestroy()
			{

			}

			void OnUpdate(Timestep ts)
			{
				//std::cout << ts.GetMilliseconds() << std::endl;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		
	}

	void EditorLayer::OnDetach()
	{
		HW_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		HW_PROFILE_FUNCTION();

		// Camera Input/VP update
		if (m_ViewportFocused)
			m_CameraController.OnUpdate(ts);

		// Reset statistics
		Renderer2D::ResetStats();
		Renderer2D::StatsBeginFrame();

		{
			HW_PROFILE_SCOPE("ClearBuffer::OnUpdate");

			// Clear frame buffer
			m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.529f, 0.808f, 0.922f, 1 });
			RenderCommand::Clear();
		}

		{
			HW_PROFILE_SCOPE("RenderDrawScene::OnUpdate");

			// Scene update
			m_Player.OnUpdate(ts);
			m_Scene->OnUpdate(ts);

			// Move camera
			glm::vec2& playerPosition = m_Player.GetPosition();
			m_CameraEntity.GetComponent<TransformComponent>().GetTransform()[3][0] =
				glm::mix(m_CameraEntity.GetComponent<TransformComponent>().GetTransform()[3][0], playerPosition.x, 0.5f);
			m_CameraEntity.GetComponent<TransformComponent>().GetTransform()[3][1] =
				glm::mix(m_CameraEntity.GetComponent<TransformComponent>().GetTransform()[3][1], playerPosition.y, 0.5f);

			m_FrameBuffer->Unbind();

			Renderer2D::StatsEndFrame();
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
				if (ImGui::MenuItem("Exit")) Application::Get().CloseApplication();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// Stats
		auto stats = Renderer2D::GetStats();
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

		// Color picker
		if (m_SquareEnt)
		{
			auto& squareColor = m_SquareEnt.GetComponent<SpriteRendererColorComponent>().Color;
			ImGui::Begin("Square Entity");
			ImGui::Text("%s", m_SquareEnt.GetComponent<TagComponent>().Tag.c_str());
			ImGui::DragFloat2("Position", glm::value_ptr(m_SquareEnt.GetComponent<TransformComponent>().GetTransform()[3]));
			ImGui::ColorEdit4("Color", glm::value_ptr(squareColor));
			ImGui::End();
		}

		// Camera mover
		ImGui::Begin("Camera Entity");
		ImGui::DragFloat2("Camera Position", glm::value_ptr(m_CameraEntity.GetComponent<TransformComponent>().GetTransform()[3]));
		ImGui::End();

		// Player mover
		ImGui::Begin("Player Entity");
		ImGui::DragFloat2("Player Position", glm::value_ptr(m_Player.GetTransform()[3]));
		ImGui::End();

		// Scene viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		ImGui::Begin("Scene Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		// Check if viewport has been resized
		if (m_ViewportSize.x != viewportPanelSize.x || m_ViewportSize.y != viewportPanelSize.y)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);

			m_Scene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		ImGui::Image((ImTextureID)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}


}