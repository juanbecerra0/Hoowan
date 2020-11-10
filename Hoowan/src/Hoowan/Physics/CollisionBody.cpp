#include "hwpch.h"
#include "CollisionBody.h"

#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"

//#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace Hoowan
{
	// Takes care of linking error
	Ref<b2World> CollisionBody::s_World = nullptr;

	void CollisionBody::Init(Ref<b2World> world)
	{
		s_World = world;
	}

	CollisionBody::CollisionBody(bool isDynamic)
		: CollisionBody(isDynamic, glm::vec2(0.0f, 0.0f))
	{
		
	}

	CollisionBody::CollisionBody(bool isDynamic, glm::vec2& position)
		: CollisionBody(isDynamic, position, glm::vec2(1.0f, 1.0f))
	{
		
	}

	CollisionBody::CollisionBody(bool isDynamic, glm::mat4& transform)
		: CollisionBody(isDynamic, glm::vec2(transform[3][0], transform[3][1]), glm::vec2(1.0f, 1.0f))
	{
		// TODO: Read scale from transform
	}

	CollisionBody::CollisionBody(bool isDynamic, glm::vec2& position, glm::vec2& scale)
	{
		// Define a body position
		b2BodyDef bodyDefinition;
		bodyDefinition.position.Set(position.x, position.y);

		if (isDynamic)
			bodyDefinition.type = b2_dynamicBody;
		else
			bodyDefinition.type = b2_staticBody;

		// Alloc the body object
		m_Body = (*s_World).CreateBody(&bodyDefinition);

		// Define a polygon
		b2PolygonShape polygonDefinition;
		polygonDefinition.SetAsBox(scale.x / 2, scale.y / 2);

		// Set fixture
		if (isDynamic)
		{
			b2FixtureDef fixtureDefinition;
			fixtureDefinition.shape = &polygonDefinition;

			fixtureDefinition.density = 1.0f;
			fixtureDefinition.friction = 0.0f;

			m_Body->CreateFixture(&fixtureDefinition);
		}
		else
		{
			m_Body->CreateFixture(&polygonDefinition, 0.0f);
		}
	}

	CollisionBody::~CollisionBody()
	{
		// Box2D takes care of memory management via the s_World reference
	}

	void CollisionBody::SetLinearVelocity(glm::vec2& velocity)
	{
		m_Body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
	}

	void CollisionBody::ApplyForce(glm::vec2& force)
	{
		m_Body->ApplyForce(b2Vec2(force.x, force.y), m_Body->GetWorldCenter(), false);
	}

	glm::mat4 CollisionBody::GetTransform()
	{
		b2Transform box2DTransform = m_Body->GetTransform();

		// Convert to a glm::mat4&
		glm::mat4 glmTransform =
			glm::translate(glm::mat4(1.0f), glm::vec3(box2DTransform.p.x, box2DTransform.p.y, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(box2DTransform.q.GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f));

		return glmTransform;
	}
}