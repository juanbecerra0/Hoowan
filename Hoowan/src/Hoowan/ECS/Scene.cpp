#include "hwpch.h"
#include "Scene.h"

#include "Hoowan/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Hoowan
{

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

		CheckForCollisions(ts);
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
				mainTransform = transform.Transform.get();
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

	void Scene::CheckForCollisions(Timestep ts)
	{
		HW_PROFILE_FUNCTION();

		auto dynamicView = m_Registry.view<Collider2DDynamicComponent>();
		auto staticView = m_Registry.view<Collider2DStaticComponent>();

		for (auto dynamicEnt : dynamicView)
		{
			auto dynamicComponent = dynamicView.get(dynamicEnt);

			for (auto staticEnt : staticView)
			{
				if (dynamicComponent.Collider.IsColliding(staticView.get(staticEnt).Collider))
				{
					// Collision detected between a dynamic component and static component
					HW_CORE_WARN("Collision detected");
				}
			}
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