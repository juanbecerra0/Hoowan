#pragma once

#include "glm/glm.hpp"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

namespace Hoowan
{
	class CollisionBody
	{
	public:
		CollisionBody(b2World& world, bool isDynamic);
		CollisionBody(b2World& world, bool isDynamic, glm::vec2& position);
		CollisionBody(b2World& world, bool isDynamic, glm::vec2& position, glm::vec2& scale);

		~CollisionBody();

	private:
		//b2BodyDef m_Body;
		b2Body* m_Body;
	};
}