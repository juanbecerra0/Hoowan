#include "hwpch.h"
#include "Entity.h"

namespace Hoowan
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}
}