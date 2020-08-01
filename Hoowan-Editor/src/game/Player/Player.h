#pragma once
#include "Hoowan.h"

#include "../Scene/SpriteSheet.h"

class Player
{
public:
	Player(Hoowan::Ref<Hoowan::Scene> scene);
	~Player();

	void OnUpdate(Hoowan::Timestep ts);

private:
	void Move(bool holdingLeft, bool holdingRight, Hoowan::Timestep ts);

	void FlipPlayerOrientation(bool flip);

private:
	Hoowan::Entity m_PlayerEntity;
	PlayerSprites m_PlayerSprites;
	
	glm::vec2 m_OriginalTexCoords[4];

	float m_Speed = 3.0f;

};