#pragma once

#include "Components.h"
#include "entt.hpp"

#include "Hoowan/Core/Timestep.h"

namespace Hoowan
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TODO: TEMP
		entt::registry& GetReg() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

	};

}