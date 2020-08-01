#include "hwpch.h"
#include "Player.h"

#include <glm\ext\matrix_transform.hpp>

Player::Player(Hoowan::Ref<Hoowan::Scene> scene)
{
	m_PlayerEntity = scene->CreateEntity("Player");

	m_PlayerEntity.AddComponent<Hoowan::SpriteRendererSubTextureComponent>(m_PlayerSprites.Idle);
	m_PlayerEntity.AddComponent<Hoowan::Collider2DDynamicComponent>(m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().Transform);
}

Player::~Player()
{

}

void Player::OnUpdate(Hoowan::Timestep ts)
{
	Move(Hoowan::Input::IsKeyPressed(Hoowan::KeyCode::A), Hoowan::Input::IsKeyPressed(Hoowan::KeyCode::D), ts);
}

void Player::Move(bool holdingLeft, bool holdingRight, Hoowan::Timestep ts)
{
	glm::mat4& transform = m_PlayerEntity.GetComponent<Hoowan::TransformComponent>().GetTransform();

	if (holdingLeft)
	{
		transform = glm::translate(transform, glm::vec3(-m_Speed, 0, 0) * ts.GetSeconds());
	}
	else if (holdingRight)
	{
		transform = glm::translate(transform, glm::vec3(m_Speed, 0, 0) * ts.GetSeconds());
	}



}

void Player::FlipPlayerOrientation(bool flip)
{
	Hoowan::SubTexture2D subTexture = m_PlayerEntity.GetComponent<Hoowan::SpriteRendererSubTextureComponent>().GetSubTexture();

	if (flip)
	{
		
	}
}
