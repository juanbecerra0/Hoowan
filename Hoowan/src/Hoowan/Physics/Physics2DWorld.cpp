#include "hwpch.h"
#include "Physics2DWorld.h"

#include "box2d/b2_math.h"

namespace Hoowan
{
	Physics2DWorld::Physics2DWorld(float gravity)
		: m_World(CreateRef<b2World>(b2Vec2(0.0f, gravity)))
	{

	}

	Physics2DWorld::~Physics2DWorld()
	{

	}

	void Physics2DWorld::SimulateFrame()
	{
		(*m_World).Step(1.0f / 60.0f, 6, 2);
	}

	void Physics2DWorld::SimulateFrame(Timestep ts)
	{
		// This may ruin everything lmao.
		// Prefer to use non-argument function (fixed 60fps)
		(*m_World).Step(ts.GetSeconds(), 6, 2);
	}

	Ref<b2World> Physics2DWorld::GetWorldReference()
	{
		return m_World;
	}

}