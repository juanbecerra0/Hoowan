#pragma once

#include "entt.hpp"

#include "Hoowan/Core/Timestep.h"

#include "Hoowan/Physics/Physics2DWorld.h"

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
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		void UpdateScriptComponents(Timestep ts);
		void HandleCollisions(Timestep ts);
		void RenderScene(Timestep ts);

		void UpdateColoredSpriteComponents(Timestep ts);
		void UpdateTexturedSpriteComponents(Timestep ts);
		void UpdateSubTexturedSpriteComponents(Timestep ts);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		Hoowan::Physics2DWorld m_PhysicsWorld;

		// Entity does not own Scene, but it must be able to reference its registry
		friend class Entity;
	};

}