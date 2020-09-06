#include "hwpch.h"
#include "CollisionBody.h"

#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"

namespace Hoowan
{
	CollisionBody::CollisionBody(b2World& world, bool isDynamic)
		: CollisionBody(world, isDynamic, glm::vec2(0.0f, 0.0f))
	{
		
	}

	CollisionBody::CollisionBody(b2World& world, bool isDynamic, glm::vec2& position)
		: CollisionBody(world, isDynamic, position, glm::vec2(1.0f, 1.0f))
	{
		
	}

	CollisionBody::CollisionBody(b2World& world, bool isDynamic, glm::vec2& position, glm::vec2& scale)
	{
		// Define a body position
		b2BodyDef bodyDefinition;
		bodyDefinition.position.Set(position.x, position.y);
		if (isDynamic) bodyDefinition.type = b2_dynamicBody;

		// Alloc the body object
		m_Body = world.CreateBody(&bodyDefinition);

		// Define a polygon
		b2PolygonShape polygonDefinition;
		polygonDefinition.SetAsBox(scale.x / 2, scale.y / 2);

		// Set fixture
		if (isDynamic)
		{
			b2FixtureDef fixtureDefinition;
			fixtureDefinition.shape = &polygonDefinition;

			fixtureDefinition.density = 1.0f;
			fixtureDefinition.friction = 0.3f;

			m_Body->CreateFixture(&fixtureDefinition);
		}
		else
		{
			m_Body->CreateFixture(&polygonDefinition, 0.0f);
		}
	}

	CollisionBody::~CollisionBody()
	{
		// TODO: Check if m_Body is being properly freed by Box2D
	}
}