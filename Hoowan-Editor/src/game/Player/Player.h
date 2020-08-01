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
	void Jump(bool holdingJump, Hoowan::Timestep ts);
	void ApplyGravity(Hoowan::Timestep ts);

	void FlipPlayerOrientation(bool flip);

private:
	Hoowan::Entity m_PlayerEntity;
	PlayerSprites m_PlayerSprites;

	glm::vec2 m_Velocity = { 0.0f, 0.0f };
	const glm::vec2 MAX_VELOCITY = { 5.0f, 9.8f };

private:
	float m_Mass = 1.8f;
	bool m_HasJumped = false;
};