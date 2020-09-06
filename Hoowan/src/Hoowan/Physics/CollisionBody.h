#pragma once

#include "glm/glm.hpp"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

namespace Hoowan
{
	class CollisionBody
	{
	public:
		static void Init(Ref<b2World> world);

		CollisionBody(bool isDynamic);
		CollisionBody(bool isDynamic, glm::vec2& position);
		CollisionBody(bool isDynamic, glm::mat4& transform);
		CollisionBody(bool isDynamic, glm::vec2& position, glm::vec2& scale);

		~CollisionBody();

		glm::mat4 GetTransform();

	private:
		static Ref<b2World> s_World;

		b2Body* m_Body;
	};
}