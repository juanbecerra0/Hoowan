#pragma once
#include "Hoowan.h"

const std::string TestLevel =
R"(
AAAAAAAAABBBBAAAA\n
aaaaaaaaabbbbaaaa\n
aaaaaaaaabbbbaaaa\n
)";

/*
Hoowan::Renderer2D::DrawStaticQuad({ -4.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Idle);
Hoowan::Renderer2D::DrawStaticQuad({ -3.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Jump);
Hoowan::Renderer2D::DrawStaticQuad({ -2.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Walk_1);
Hoowan::Renderer2D::DrawStaticQuad({ -1.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Walk_2);
Hoowan::Renderer2D::DrawStaticQuad({ 00.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Climb_1);
Hoowan::Renderer2D::DrawStaticQuad({ 01.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Climb_2);
Hoowan::Renderer2D::DrawStaticQuad({ 02.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Crouch);
Hoowan::Renderer2D::DrawStaticQuad({ 03.0f, 1.0f }, { 0.5f, 0.5f }, m_PlayerSprites.Victory);

Hoowan::Renderer2D::DrawStaticQuad({ 00.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenLand);
Hoowan::Renderer2D::DrawStaticQuad({ 01.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenStone);
Hoowan::Renderer2D::DrawStaticQuad({ 02.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenLandJag);
Hoowan::Renderer2D::DrawStaticQuad({ 03.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenStoneJag);

Hoowan::Renderer2D::DrawStaticQuad({ 04.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SandLand);
Hoowan::Renderer2D::DrawStaticQuad({ 05.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SandStone);
Hoowan::Renderer2D::DrawStaticQuad({ 06.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SandLandJag);
Hoowan::Renderer2D::DrawStaticQuad({ 07.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SandStoneJag);

Hoowan::Renderer2D::DrawStaticQuad({ 08.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SnowLand);
Hoowan::Renderer2D::DrawStaticQuad({ 09.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SnowStone);
Hoowan::Renderer2D::DrawStaticQuad({ 10.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SnowLandJag);
Hoowan::Renderer2D::DrawStaticQuad({ 11.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.SnowStoneJag);

Hoowan::Renderer2D::DrawStaticQuad({ 12.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.LandUnder);
Hoowan::Renderer2D::DrawStaticQuad({ 13.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.StoneUnder);

Hoowan::Renderer2D::DrawStaticQuad({ 14.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.WaterSurface);
Hoowan::Renderer2D::DrawStaticQuad({ 15.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.WaterDepths);
Hoowan::Renderer2D::DrawStaticQuad({ 16.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.LavaSurface);
Hoowan::Renderer2D::DrawStaticQuad({ 17.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.LavaDepths);

Hoowan::Renderer2D::DrawStaticQuad({ 18.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GoldBlock);
Hoowan::Renderer2D::DrawStaticQuad({ 19.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GoldBlockAlt);
Hoowan::Renderer2D::DrawStaticQuad({ 20.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BrownBlock);
Hoowan::Renderer2D::DrawStaticQuad({ 21.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BrownBlockAlt);
Hoowan::Renderer2D::DrawStaticQuad({ 22.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreyBlock);
Hoowan::Renderer2D::DrawStaticQuad({ 23.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreyBlockAlt);
Hoowan::Renderer2D::DrawStaticQuad({ 24.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.WoodBlock);
Hoowan::Renderer2D::DrawStaticQuad({ 25.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.WoodBlockAlt);

Hoowan::Renderer2D::DrawStaticQuad({ 26.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.LadderTop);
Hoowan::Renderer2D::DrawStaticQuad({ 27.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.LadderStep);

Hoowan::Renderer2D::DrawStaticQuad({ 28.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.Bridge);
Hoowan::Renderer2D::DrawStaticQuad({ 29.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GrassPatch);
Hoowan::Renderer2D::DrawStaticQuad({ 30.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.Spikes);
Hoowan::Renderer2D::DrawStaticQuad({ 31.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.Spinner);

Hoowan::Renderer2D::DrawStaticQuad({ 32.0f, 0.25f }, { 0.5f, 1.0f }, m_PlatformSprites.OpenDoor);
Hoowan::Renderer2D::DrawStaticQuad({ 33.0f, 0.25f }, { 0.5f, 1.0f }, m_PlatformSprites.BlueDoor);
Hoowan::Renderer2D::DrawStaticQuad({ 34.0f, 0.25f }, { 0.5f, 1.0f }, m_PlatformSprites.YellowDoor);
Hoowan::Renderer2D::DrawStaticQuad({ 35.0f, 0.25f }, { 0.5f, 1.0f }, m_PlatformSprites.GreenDoor);
Hoowan::Renderer2D::DrawStaticQuad({ 36.0f, 0.25f }, { 0.5f, 1.0f }, m_PlatformSprites.RedDoor);

Hoowan::Renderer2D::DrawStaticQuad({ 37.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.NoticeWhite);
Hoowan::Renderer2D::DrawStaticQuad({ 38.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.NoticeGreen);
Hoowan::Renderer2D::DrawStaticQuad({ 39.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.NoticeRed);

Hoowan::Renderer2D::DrawStaticQuad({ 40.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueBlockClosed);
Hoowan::Renderer2D::DrawStaticQuad({ 41.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueBlockOpen);
Hoowan::Renderer2D::DrawStaticQuad({ 42.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowBlockClosed);
Hoowan::Renderer2D::DrawStaticQuad({ 43.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowBlockOpen);
Hoowan::Renderer2D::DrawStaticQuad({ 44.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenBlockClosed);
Hoowan::Renderer2D::DrawStaticQuad({ 45.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenBlockOpen);
Hoowan::Renderer2D::DrawStaticQuad({ 46.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedBlockClosed);
Hoowan::Renderer2D::DrawStaticQuad({ 47.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedBlockOpen);

Hoowan::Renderer2D::DrawStaticQuad({ 48.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueButtonUp);
Hoowan::Renderer2D::DrawStaticQuad({ 49.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueButtonDown);
Hoowan::Renderer2D::DrawStaticQuad({ 50.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowButtonUp);
Hoowan::Renderer2D::DrawStaticQuad({ 51.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowButtonDown);
Hoowan::Renderer2D::DrawStaticQuad({ 52.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenButtonUp);
Hoowan::Renderer2D::DrawStaticQuad({ 53.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenButtonDown);
Hoowan::Renderer2D::DrawStaticQuad({ 54.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedButtonUp);
Hoowan::Renderer2D::DrawStaticQuad({ 55.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedButtonDown);

Hoowan::Renderer2D::DrawStaticQuad({ 56.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BluePortal);
Hoowan::Renderer2D::DrawStaticQuad({ 57.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowPortal);
Hoowan::Renderer2D::DrawStaticQuad({ 58.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenPortal);
Hoowan::Renderer2D::DrawStaticQuad({ 59.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedPortal);

Hoowan::Renderer2D::DrawStaticQuad({ 60.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlankCrystal);
Hoowan::Renderer2D::DrawStaticQuad({ 61.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueCrystal);
Hoowan::Renderer2D::DrawStaticQuad({ 62.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowCrystal);
Hoowan::Renderer2D::DrawStaticQuad({ 63.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenCrystal);
Hoowan::Renderer2D::DrawStaticQuad({ 64.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedCrystal);

Hoowan::Renderer2D::DrawStaticQuad({ 65.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlankGem);
Hoowan::Renderer2D::DrawStaticQuad({ 66.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueGem);
Hoowan::Renderer2D::DrawStaticQuad({ 67.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowGem);
Hoowan::Renderer2D::DrawStaticQuad({ 68.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenGem);
Hoowan::Renderer2D::DrawStaticQuad({ 69.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedGem);

Hoowan::Renderer2D::DrawStaticQuad({ 70.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlankKey);
Hoowan::Renderer2D::DrawStaticQuad({ 71.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.BlueKey);
Hoowan::Renderer2D::DrawStaticQuad({ 72.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.YellowKey);
Hoowan::Renderer2D::DrawStaticQuad({ 73.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.GreenKey);
Hoowan::Renderer2D::DrawStaticQuad({ 74.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.RedKey);

Hoowan::Renderer2D::DrawStaticQuad({ 75.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.HeartEmpty);
Hoowan::Renderer2D::DrawStaticQuad({ 76.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.HeartHalf);
Hoowan::Renderer2D::DrawStaticQuad({ 77.0f, 0.0f }, { 0.5f, 0.5f }, m_PlatformSprites.HeartFull);
*/