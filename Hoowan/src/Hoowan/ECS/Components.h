#pragma once

#include "glm/glm.hpp"
#include "Hoowan/Renderer/Texture.h"
#include "Hoowan/Renderer/SubTexture2D.h"
#include "Hoowan/Physics/RectangleCollider.h"
#include <Hoowan\ECS\SceneCamera.h>

namespace Hoowan
{
	struct TagComponent
	{
		std::string Tag;

		// Constructors
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag) {};
	};

	struct TransformComponent
	{
		Ref<glm::mat4> Transform = CreateRef<glm::mat4>(glm::mat4(1.0f));

		glm::mat4& GetTransform() { return *Transform; }

		// Constructors
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Ref<glm::mat4> transform) : Transform(transform) {}

		operator glm::mat4& () { return *Transform; }
		operator const glm::mat4& () const { return *Transform; }
	};

	struct SpriteRendererColorComponent
	{
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };

		// Constructors
		SpriteRendererColorComponent() = default;
		SpriteRendererColorComponent(const SpriteRendererColorComponent&) = default;
		SpriteRendererColorComponent(const glm::vec4& color) : Color(color) {}

	};

	struct SpriteRendererTextureComponent
	{
		Hoowan::Ref<Texture2D> Texture;

		Texture2D& GetTexture() { return *Texture; }
		void SetTexture(Texture2D& texture) { *Texture = texture; }

		// Constructors
		SpriteRendererTextureComponent() = default;
		SpriteRendererTextureComponent(const SpriteRendererTextureComponent&) = default;
		SpriteRendererTextureComponent(const Ref<Texture2D> texture) : Texture(texture) {}
	};

	struct SpriteRendererSubTextureComponent
	{
		Hoowan::Ref<SubTexture2D> SubTexture;

		SubTexture2D& GetSubTexture() { return *SubTexture; }
		void SetSubTexture(SubTexture2D& subTexture) { *SubTexture = subTexture; }

		// Constructors
		SpriteRendererSubTextureComponent() = default;
		SpriteRendererSubTextureComponent(const SpriteRendererSubTextureComponent&) = default;
		SpriteRendererSubTextureComponent(const Ref<SubTexture2D> subTexture) : SubTexture(subTexture) {}
	};

	struct CameraComponent
	{
		Hoowan::SceneCamera Camera;
		bool IsPrimary = false;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct Collider2DStaticComponent
	{
		RectangleCollider Collider;

		Collider2DStaticComponent() = default;
		Collider2DStaticComponent(const Collider2DStaticComponent&) = default;
		Collider2DStaticComponent(Ref<glm::mat4> transform) : Collider(transform) {}
		Collider2DStaticComponent(Ref<glm::mat4> transform, const glm::vec2 dimensions) : Collider(transform, dimensions) {}
	};

	struct Collider2DDynamicComponent
	{
		RectangleCollider Collider;
		glm::vec2 PreviousPosition = { 0.0f, 0.0f };

		Collider2DDynamicComponent() = default;
		Collider2DDynamicComponent(const Collider2DDynamicComponent&) = default;
		Collider2DDynamicComponent(Ref<glm::mat4> transform) : Collider(transform), PreviousPosition((*transform)[3]) {}
		Collider2DDynamicComponent(Ref<glm::mat4> transform, const glm::vec2 dimensions) : Collider(transform, dimensions), PreviousPosition((*transform)[3]) {}
	};
}