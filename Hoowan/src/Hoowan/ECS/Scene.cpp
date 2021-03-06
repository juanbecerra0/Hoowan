#include "hwpch.h"
#include "Scene.h"

#include "Hoowan/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

#include "Components.h"

namespace Hoowan
{

	Scene::Scene()
		: m_PhysicsWorld(-9.8f)
	{
		CollisionBody::Init(m_PhysicsWorld.GetWorldReference());
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

		UpdateScriptComponents(ts);
		HandleCollisions(ts);
		RenderScene(ts);
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize non-fixed aspect ratio camera
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);
			if (!camera.FixedAspectRatio)
				camera.Camera.SetViewportSize(width, height);

		}
	}

	void Scene::UpdateScriptComponents(Timestep ts)
	{
		HW_PROFILE_FUNCTION();

		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			// TODO: Move to Scene::OnScenePlay()
			// TODO: Implement Scene::OnSceneEnd()
			if (!nsc.Instance)
			{
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}

			nsc.Instance->OnUpdate(ts);
		});
	}

	void Scene::HandleCollisions(Timestep ts)
	{
		HW_PROFILE_FUNCTION();

		// Simulate the world
		m_PhysicsWorld.SimulateFrame(ts);

		// Update the transform components of possibly-moved objects
		// TODO: Optimize to only trigger on dynamic objects
		auto group = m_Registry.group<>(entt::get<TransformComponent, CollisionComponent>);
		for (auto entity : group)
		{
			auto& [transform, collider] = group.get<TransformComponent, CollisionComponent>(entity);

			transform.SetTransform(collider.GetTransform());
		}
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
				mainTransform = &transform.GetTransform();
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