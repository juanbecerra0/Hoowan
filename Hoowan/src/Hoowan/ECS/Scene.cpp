#include "hwpch.h"
#include "Scene.h"

#include "Hoowan/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

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

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };

		// All entities must contain a tag and a transform component
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		entity.AddComponent<TransformComponent>();

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		HW_PROFILE_FUNCTION()
		//UpdateColoredSpriteComponents(ts);
		//UpdateTexturedSpriteComponents(ts);
		UpdateSubTexturedSpriteComponents(ts);
	}

	void Scene::UpdateColoredSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererColorComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererColorComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

	void Scene::UpdateTexturedSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererTextureComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererTextureComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Texture);
		}
	}

	void Scene::UpdateSubTexturedSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererSubTextureComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererSubTextureComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.SubTexture);
		}
	}

}