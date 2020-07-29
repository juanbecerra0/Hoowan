#include "hwpch.h"
#include "Scene.h"

#include "Hoowan/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Hoowan
{

/*

static void AFunction(entt::registry& registry, entt::entity entity) {}

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

		RenderScene(ts);
	}

	void Scene::RenderScene(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		Camera* mainCamera = nullptr;
		glm::mat4* mainTransform = nullptr;

		auto group = m_Registry.group<>(entt::get<TransformComponent, CameraComponent>);
		for (auto entity : group)
		{
			auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

			if (camera.IsPrimary)
			{
				mainCamera = &camera.Camera;
				mainTransform = &transform.Transform;
				break;
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *mainTransform);

			UpdateColoredSpriteComponents(ts);
			UpdateTexturedSpriteComponents(ts);
			UpdateSubTexturedSpriteComponents(ts);

			Renderer2D::EndScene();
		}

	}

	void Scene::UpdateColoredSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<>(entt::get<TransformComponent, SpriteRendererColorComponent>);
		//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererColorComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererColorComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

	void Scene::UpdateTexturedSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<>(entt::get<TransformComponent, SpriteRendererTextureComponent>);
		//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererTextureComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererTextureComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Texture);
		}
	}

	void Scene::UpdateSubTexturedSpriteComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION()

		auto group = m_Registry.group<>(entt::get<TransformComponent, SpriteRendererSubTextureComponent>);
		//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererSubTextureComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererSubTextureComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.SubTexture);
		}
	}

}