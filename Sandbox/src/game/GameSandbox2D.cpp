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

	m_PlayerSpritesheet = Hoowan::Texture2D::Create("assets/gametiles/player.png");
	m_PlatformsSpritesheet = Hoowan::Texture2D::Create("assets/gametiles/platforms.png");

	m_GreenLand =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f , 6.0f }, { 128.0f, 128.0f });
	m_OpenDoor =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 5.0f, 0.0f, }, { 128.0f, 256.0f });

	m_GreenLand =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 6.0f }, { 128.0f, 128.0f });
	m_GreenStone =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 5.0f }, { 128.0f, 128.0f });
	m_GreenLandJag =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 4.0f }, { 128.0f, 128.0f });
	m_GreenStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 3.0f }, { 128.0f, 128.0f });
	
	m_SandLand =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 6.0f }, { 128.0f, 128.0f });
	m_SandStone =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 5.0f }, { 128.0f, 128.0f });
	m_SandLandJag =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 4.0f }, { 128.0f, 128.0f });
	m_SandStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 3.0f }, { 128.0f, 128.0f });
	
	m_SnowLand =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 6.0f }, { 128.0f, 128.0f });
	m_SnowStone =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 5.0f }, { 128.0f, 128.0f });
	m_SnowLandJag =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 4.0f }, { 128.0f, 128.0f });
	m_SnowStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 3.0f }, { 128.0f, 128.0f });
	
	m_LandUnder =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 6.0f }, { 128.0f, 128.0f });
	m_StoneUnder =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 5.0f }, { 128.0f, 128.0f });
	
	m_WaterSurface =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 6.0f }, { 128.0f, 128.0f });
	m_WaterDepths =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 5.0f }, { 128.0f, 128.0f });
	m_LavaSurface =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 5.0f, 6.0f }, { 128.0f, 128.0f });
	m_LavaDepths =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 5.0f, 5.0f }, { 128.0f, 128.0f });
	
	m_GoldBlock =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 4.0f }, { 128.0f, 128.0f });
	m_GoldBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 4.0f }, { 128.0f, 128.0f });
	m_BrownBlock =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 3.0f }, { 128.0f, 128.0f });
	m_BrownBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 3.0f }, { 128.0f, 128.0f });
	m_GreyBlock =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 2.0f }, { 128.0f, 128.0f });
	m_GreyBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 2.0f }, { 128.0f, 128.0f });
	m_WoodBlock =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 3.0f, 1.0f }, { 128.0f, 128.0f });
	m_WoodBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 4.0f, 1.0f }, { 128.0f, 128.0f });
	
	m_LadderTop =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 2.0f }, { 128.0f, 128.0f });
	m_LadderStep =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 2.0f }, { 128.0f, 128.0f });

	m_Bridge =			Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 2.0f }, { 128.0f, 128.0f });
	m_GrassPatch =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 2.0f, 1.0f }, { 128.0f, 128.0f });
	m_Spikes =			Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 0.0f, 1.0f }, { 128.0f, 128.0f });
	m_Spinner =			Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 1.0f, 1.0f }, { 128.0f, 128.0f });

	m_OpenDoor =		Hoowan::SubTexture2D::CreateFromCoords(m_PlatformsSpritesheet, { 5.0f, 0.0f }, { 128.0f, 256.0f });
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

		Hoowan::Renderer2D::DrawStaticQuad({ 00.0f, 0.0f }, { 0.5f, 0.5f }, m_GreenLand);
		Hoowan::Renderer2D::DrawStaticQuad({ 01.0f, 0.0f }, { 0.5f, 0.5f }, m_GreenStone);
		Hoowan::Renderer2D::DrawStaticQuad({ 02.0f, 0.0f }, { 0.5f, 0.5f }, m_GreenLandJag);
		Hoowan::Renderer2D::DrawStaticQuad({ 03.0f, 0.0f }, { 0.5f, 0.5f }, m_GreenStoneJag);

		Hoowan::Renderer2D::DrawStaticQuad({ 04.0f, 0.0f }, { 0.5f, 0.5f }, m_SandLand);
		Hoowan::Renderer2D::DrawStaticQuad({ 05.0f, 0.0f }, { 0.5f, 0.5f }, m_SandStone);
		Hoowan::Renderer2D::DrawStaticQuad({ 06.0f, 0.0f }, { 0.5f, 0.5f }, m_SandLandJag);
		Hoowan::Renderer2D::DrawStaticQuad({ 07.0f, 0.0f }, { 0.5f, 0.5f }, m_SandStoneJag);

		Hoowan::Renderer2D::DrawStaticQuad({ 08.0f, 0.0f }, { 0.5f, 0.5f }, m_SnowLand);
		Hoowan::Renderer2D::DrawStaticQuad({ 09.0f, 0.0f }, { 0.5f, 0.5f }, m_SnowStone);
		Hoowan::Renderer2D::DrawStaticQuad({ 10.0f, 0.0f }, { 0.5f, 0.5f }, m_SnowLandJag);
		Hoowan::Renderer2D::DrawStaticQuad({ 11.0f, 0.0f }, { 0.5f, 0.5f }, m_SnowStoneJag);

		Hoowan::Renderer2D::DrawStaticQuad({ 12.0f, 0.0f }, { 0.5f, 0.5f }, m_LandUnder);
		Hoowan::Renderer2D::DrawStaticQuad({ 13.0f, 0.0f }, { 0.5f, 0.5f }, m_StoneUnder);

		Hoowan::Renderer2D::DrawStaticQuad({ 14.0f, 0.0f }, { 0.5f, 0.5f }, m_WaterSurface);
		Hoowan::Renderer2D::DrawStaticQuad({ 15.0f, 0.0f }, { 0.5f, 0.5f }, m_WaterDepths);
		Hoowan::Renderer2D::DrawStaticQuad({ 16.0f, 0.0f }, { 0.5f, 0.5f }, m_LavaSurface);
		Hoowan::Renderer2D::DrawStaticQuad({ 17.0f, 0.0f }, { 0.5f, 0.5f }, m_LavaDepths);

		Hoowan::Renderer2D::DrawStaticQuad({ 18.0f, 0.0f }, { 0.5f, 0.5f }, m_GoldBlock);
		Hoowan::Renderer2D::DrawStaticQuad({ 19.0f, 0.0f }, { 0.5f, 0.5f }, m_GoldBlockAlt);
		Hoowan::Renderer2D::DrawStaticQuad({ 20.0f, 0.0f }, { 0.5f, 0.5f }, m_BrownBlock);
		Hoowan::Renderer2D::DrawStaticQuad({ 21.0f, 0.0f }, { 0.5f, 0.5f }, m_BrownBlockAlt);
		Hoowan::Renderer2D::DrawStaticQuad({ 22.0f, 0.0f }, { 0.5f, 0.5f }, m_GreyBlock);
		Hoowan::Renderer2D::DrawStaticQuad({ 23.0f, 0.0f }, { 0.5f, 0.5f }, m_GreyBlockAlt);
		Hoowan::Renderer2D::DrawStaticQuad({ 24.0f, 0.0f }, { 0.5f, 0.5f }, m_WoodBlock);
		Hoowan::Renderer2D::DrawStaticQuad({ 25.0f, 0.0f }, { 0.5f, 0.5f }, m_WoodBlockAlt);

		Hoowan::Renderer2D::DrawStaticQuad({ 26.0f, 0.0f }, { 0.5f, 0.5f }, m_LadderTop);
		Hoowan::Renderer2D::DrawStaticQuad({ 27.0f, 0.0f }, { 0.5f, 0.5f }, m_LadderStep);

		Hoowan::Renderer2D::DrawStaticQuad({ 28.0f, 0.0f }, { 0.5f, 0.5f }, m_Bridge);
		Hoowan::Renderer2D::DrawStaticQuad({ 29.0f, 0.0f }, { 0.5f, 0.5f }, m_GrassPatch);
		Hoowan::Renderer2D::DrawStaticQuad({ 30.0f, 0.0f }, { 0.5f, 0.5f }, m_Spikes);
		Hoowan::Renderer2D::DrawStaticQuad({ 31.0f, 0.0f }, { 0.5f, 0.5f }, m_Spinner);

		Hoowan::Renderer2D::DrawStaticQuad({ 32.0f, 0.5f }, { 0.5f, 1.0f }, m_OpenDoor);

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
