#include "hwpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace Hoowan
{

/*

static void AFunction(entt::registry& registry, entt::entity entity) {}

struct MeshComponent {};

struct TransformComponent
{
	glm::mat4 Transform;

	// Constructors
	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::mat4& transform) : Transform(transform) {}

	// Easy casts
	operator glm::mat4& () { return Transform; }
	operator const glm::mat4& () const { return Transform; }
};

// Ent is the ID of the new component placed in m_Registry
entt::entity ent = m_Registry.create();
m_Registry.emplace<TransformComponent>(ent, glm::mat4(1.0f));


// Get a reference to the transform component
if (m_Registry.has<TransformComponent>(ent))
	TransformComponent& trans = m_Registry.get<TransformComponent>(ent);

// Iterate through each transform component in registry
auto view = m_Registry.view<TransformComponent>();
for (auto e : view)
{
	TransformComponent& trans = m_Registry.get<TransformComponent>(e);
}

// Get entities that contain both a transform and mesh and save as a pair
auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
for (auto e : group)
{
	auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(e);
}

// Tie registry events to functions
m_Registry.on_construct<TransformComponent>().connect<&AFunction>();

// Remove entity
m_Registry.remove<TransformComponent>(ent);
*/

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

}