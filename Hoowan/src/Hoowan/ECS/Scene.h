#pragma once

#include "Components.h"
#include "entt.hpp"

#include "Hoowan/Core/Timestep.h"

namespace Hoowan
{
	// Forward-declared
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);

	private:
		void CheckForCollisions(Timestep ts);
		void RenderScene(Timestep ts);

		void UpdateColoredSpriteComponents(Timestep ts);
		void UpdateTexturedSpriteComponents(Timestep ts);
		void UpdateSubTexturedSpriteComponents(Timestep ts);

	private:
		entt::registry m_Registry;

		// Entity does not own Scene, but it must be able to reference its registry
		friend class Entity;
	};

}