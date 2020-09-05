#pragma once

#include "box2d/b2_world.h"

namespace Hoowan
{
	class Physics2DWorld
	{
	public:
		Physics2DWorld(float gravity);
		~Physics2DWorld();

	private:
		b2World m_World;
	};
}
