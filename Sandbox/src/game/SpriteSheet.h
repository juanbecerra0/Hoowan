#pragma once
#include "Hoowan.h"

struct PlatformSprites
{
private:
	Hoowan::Ref<Hoowan::Texture2D> PlatformSpritesheet = Hoowan::Texture2D::Create("assets/gametiles/platforms.png");

public:
	// Green surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> GreenLand =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f , 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenStone =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenLandJag =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f, 3.0f }, { 128.0f, 128.0f });

	// Sand surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> SandLand =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SandStone =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SandLandJag =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SandStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 3.0f }, { 128.0f, 128.0f });

	// Snow surfaces
	Hoowan::Ref<Hoowan::SubTexture2D> SnowLand =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SnowStone =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SnowLandJag =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> SnowStoneJag =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 3.0f }, { 128.0f, 128.0f });

	// Underground
	Hoowan::Ref<Hoowan::SubTexture2D> LandUnder =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> StoneUnder =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 5.0f }, { 128.0f, 128.0f });

	// Fluids
	Hoowan::Ref<Hoowan::SubTexture2D> WaterSurface =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> WaterDepths =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> LavaSurface =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> LavaDepths =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 5.0f }, { 128.0f, 128.0f });

	// Blocks
	Hoowan::Ref<Hoowan::SubTexture2D> GoldBlock =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GoldBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BrownBlock =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BrownBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreyBlock =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreyBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> WoodBlock =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 3.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> WoodBlockAlt =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 4.0f, 1.0f }, { 128.0f, 128.0f });

	// Ladder
	Hoowan::Ref<Hoowan::SubTexture2D> LadderTop =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> LadderStep =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 2.0f }, { 128.0f, 128.0f });

	// Misc
	Hoowan::Ref<Hoowan::SubTexture2D> Bridge =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GrassPatch =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 2.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Spikes =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 0.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Spinner =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 1.0f, 1.0f }, { 128.0f, 128.0f });

	// Doors
	Hoowan::Ref<Hoowan::SubTexture2D> OpenDoor =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 0.0f }, { 128.0f, 256.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueDoor =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 0.0f }, { 128.0f, 256.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowDoor =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 0.0f }, { 128.0f, 256.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenDoor =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 0.0f }, { 128.0f, 256.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedDoor =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 0.0f }, { 128.0f, 256.0f });

	// Notices
	Hoowan::Ref<Hoowan::SubTexture2D> NoticeWhite =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> NoticeGreen =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> NoticeRed	=		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 5.0f, 4.0f }, { 128.0f, 128.0f });

	// Colored blocks
	Hoowan::Ref<Hoowan::SubTexture2D> BlueBlockClosed =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueBlockOpen =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowBlockClosed=Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowBlockOpen = Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenBlockClosed =Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenBlockOpen =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedBlockClosed =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedBlockOpen =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 5.0f }, { 128.0f, 128.0f });

	// Buttons
	Hoowan::Ref<Hoowan::SubTexture2D> BlueButtonUp =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueButtonDown =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowButtonUp =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 12.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowButtonDown =Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 13.0f, 1.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenButtonUp =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 0.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenButtonDown = Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 0.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedButtonUp =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 12.0f, 0.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedButtonDown =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 13.0f, 0.0f }, { 128.0f, 128.0f });

	// Portals
	Hoowan::Ref<Hoowan::SubTexture2D> BluePortal =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowPortal =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 6.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenPortal =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 5.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedPortal =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 5.0f }, { 128.0f, 128.0f });

	// Crystals
	Hoowan::Ref<Hoowan::SubTexture2D> BlankCrystal =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueCrystal =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowCrystal =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenCrystal =	Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedCrystal =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 4.0f }, { 128.0f, 128.0f });

	// Gems
	Hoowan::Ref<Hoowan::SubTexture2D> BlankGem =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueGem =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowGem =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenGem =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedGem =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 3.0f }, { 128.0f, 128.0f });

	// Keys
	Hoowan::Ref<Hoowan::SubTexture2D> BlankKey =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 6.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> BlueKey =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 7.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> YellowKey =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 8.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> GreenKey =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 9.0f, 2.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> RedKey =			Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 10.0f, 2.0f }, { 128.0f, 128.0f });

	// Hearts
	Hoowan::Ref<Hoowan::SubTexture2D> HeartEmpty =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 4.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> HeartHalf =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 3.0f }, { 128.0f, 128.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> HeartFull =		Hoowan::SubTexture2D::CreateFromCoords(PlatformSpritesheet, { 11.0f, 2.0f }, { 128.0f, 128.0f });
};

struct PlayerSprites
{
private:
	Hoowan::Ref<Hoowan::Texture2D> PlayerSpritesheet =	Hoowan::Texture2D::Create("assets/gametiles/player.png");

public:
	Hoowan::Ref<Hoowan::SubTexture2D> Idle =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 0.0f, 1.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Jump =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 1.0f, 1.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Walk_1 =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 2.0f, 1.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Walk_2 =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 3.0f, 1.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Climb_1 =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 0.0f, 0.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Climb_2 =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 1.0f, 0.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Crouch =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 2.0f, 0.0f }, { 192.0f, 192.0f });
	Hoowan::Ref<Hoowan::SubTexture2D> Victory =			Hoowan::SubTexture2D::CreateFromCoords(PlayerSpritesheet, { 3.0f, 0.0f }, { 192.0f, 192.0f });
};