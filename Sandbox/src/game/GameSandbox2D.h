#pragma once

#include "Hoowan.h"

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
	Hoowan::OrthographicCameraController m_CameraController;

	// Spritesheets
	Hoowan::Ref<Hoowan::Texture2D> m_PlayerSpritesheet;
	Hoowan::Ref<Hoowan::Texture2D> m_PlatformsSpritesheet;

	/////////////////////////////////////////////
	////////////////// Sprites //////////////////
	/////////////////////////////////////////////

	// Green surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreenLand;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreenStone;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreenLandJag;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreenStoneJag;

	// Sand surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> m_SandLand;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SandStone;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SandLandJag;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SandStoneJag;

	// Snow surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> m_SnowLand;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SnowStone;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SnowLandJag;
	Hoowan::Ref<Hoowan::SubTexture2D> m_SnowStoneJag;

	// Underground
	Hoowan::Ref<Hoowan::SubTexture2D> m_LandUnder;
	Hoowan::Ref<Hoowan::SubTexture2D> m_StoneUnder;

	// Fluids
	Hoowan::Ref<Hoowan::SubTexture2D> m_WaterSurface;
	Hoowan::Ref<Hoowan::SubTexture2D> m_WaterDepths;
	Hoowan::Ref<Hoowan::SubTexture2D> m_LavaSurface;
	Hoowan::Ref<Hoowan::SubTexture2D> m_LavaDepths;

	// Blocks
	Hoowan::Ref<Hoowan::SubTexture2D> m_GoldBlock;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GoldBlockAlt;
	Hoowan::Ref<Hoowan::SubTexture2D> m_BrownBlock;
	Hoowan::Ref<Hoowan::SubTexture2D> m_BrownBlockAlt;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreyBlock;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GreyBlockAlt;
	Hoowan::Ref<Hoowan::SubTexture2D> m_WoodBlock;
	Hoowan::Ref<Hoowan::SubTexture2D> m_WoodBlockAlt;

	// Ladder
	Hoowan::Ref<Hoowan::SubTexture2D> m_LadderTop;
	Hoowan::Ref<Hoowan::SubTexture2D> m_LadderStep;

	// Misc
	Hoowan::Ref<Hoowan::SubTexture2D> m_Bridge;
	Hoowan::Ref<Hoowan::SubTexture2D> m_GrassPatch;
	Hoowan::Ref<Hoowan::SubTexture2D> m_Spikes;
	Hoowan::Ref<Hoowan::SubTexture2D> m_Spinner;

	Hoowan::Ref<Hoowan::SubTexture2D> m_OpenDoor;
};