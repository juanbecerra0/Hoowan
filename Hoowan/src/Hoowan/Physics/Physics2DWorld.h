#pragma once

#include "box2d/b2_world.h"

namespace Hoowan
{
	class Physics2DWorld
	{
	public:
		Physics2DWorld(float gravity);
		~Physics2DWorld();

		void SimulateWorld();

		Ref<b2World> GetWorldReference();

	private:
		Ref<b2World> m_World;
	};
}
