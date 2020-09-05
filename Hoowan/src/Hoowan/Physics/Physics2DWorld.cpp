#include "hwpch.h"
#include "Physics2DWorld.h"

#include "box2d/b2_math.h"

namespace Hoowan
{
	Physics2DWorld::Physics2DWorld(float gravity)
		: m_World({ 0.0f, gravity })
	{

	}

	Physics2DWorld::~Physics2DWorld()
	{

	}

}