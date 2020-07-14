#pragma once
#include "entt.hpp"

namespace Hoowan
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;

	};

}