#include "Sandbox2D.h"
#include "Hoowan/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

// Test timer
template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })
// ! Test Timer

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
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");

		// Camera Input/VP update
		m_CameraController.OnUpdate(ts);
	}

	{
		PROFILE_SCOPE("ClearBuffer::OnUpdate");

		// Clear frame buffer
		Hoowan::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hoowan::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("RenderScene::OnUpdate");

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
	// Color selection
	ImGui::Begin("Color Selector");

	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));

	ImGui::End();


	// Profiler
	ImGui::Begin("Profiler");

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "  %.3fms :: ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();

}

void Sandbox2D::OnEvent(Hoowan::Event& e)
{
	m_CameraController.OnEvent(e);
}
