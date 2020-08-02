#include "hwpch.h"
#include "Player.h"

#include <glm\ext\matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>

Player::Player(Hoowan::Ref<Hoowan::Scene> scene, glm::vec2& startingPosition)
{
	m_PlayerEntity = scene->CreateEntity("Player");
	m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().GetTransform()[3][0] = startingPosition.x;
	m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().GetTransform()[3][1] = startingPosition.y;

	m_PlayerEntity.AddComponent<Hoowan::SpriteRendererSubTextureComponent>(m_PlayerSprites.Idle);
	m_PlayerEntity.AddComponent<Hoowan::Collider2DDynamicComponent>(m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().Transform);
}

Player::~Player()
{

}

void Player::OnUpdate(Hoowan::Timestep ts)
{
	// Modify velocity with these methods
	Move(Hoowan::Input::IsKeyPressed(Hoowan::KeyCode::A), Hoowan::Input::IsKeyPressed(Hoowan::KeyCode::D), ts);
	Jump(Hoowan::Input::IsKeyPressed(Hoowan::KeyCode::Space), ts);
	ApplyGravity(ts);

	// Apply transformation
	glm::mat4& transform = m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().GetTransform();
	transform = glm::translate(transform, glm::vec3(m_Velocity.x, m_Velocity.y, 0.0f) * ts.GetSeconds());
}

// Util

void Player::Move(bool holdingLeft, bool holdingRight, Hoowan::Timestep ts)
{
	if (holdingLeft)
	{
		m_Velocity.x = -MAX_VELOCITY.x;
		FlipPlayerOrientation(true);
	}
	else if (holdingRight)
	{
		m_Velocity.x = MAX_VELOCITY.x;
		FlipPlayerOrientation(false);
	}
	else
	{
		m_Velocity.x = 0.0f;
	}
}

void Player::Jump(bool holdingJump, Hoowan::Timestep ts)
{
	if (holdingJump && !m_HasJumped)
	{
		m_HasJumped = true;

		m_Velocity.y = MAX_VELOCITY.y;
	}
	else if (!holdingJump)
	{
		m_HasJumped = false;
	}
}

void Player::ApplyGravity(Hoowan::Timestep ts)
{
	m_Velocity.y = std::clamp(m_Velocity.y - (MAX_VELOCITY.y * m_Mass * ts.GetSeconds()), -MAX_VELOCITY.y, MAX_VELOCITY.y);
}

void Player::FlipPlayerOrientation(bool flip)
{
	Hoowan::SubTexture2D& subTexture = m_PlayerEntity.GetComponent<Hoowan::SpriteRendererSubTextureComponent>().GetSubTexture();
	flip ? subTexture.FlipOrientation(false, true) : subTexture.FlipOrientation(false, false);
}
