#pragma once

#include "Hoowan/Core/Timestep.h"

#include "box2d/b2_world.h"

namespace Hoowan
{
	class Physics2DWorld
	{
	public:
		Physics2DWorld(float gravity);
		~Physics2DWorld();

		void SimulateFrame();
		void SimulateFrame(Timestep ts);

		Ref<b2World> GetWorldReference();

	private:
		Ref<b2World> m_World;
	};
}
