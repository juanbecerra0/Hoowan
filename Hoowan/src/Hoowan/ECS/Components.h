#pragma once

#include "glm/glm.hpp"
#include "Hoowan/Renderer/Texture.h"
#include "Hoowan/Renderer/SubTexture2D.h"

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
		glm::mat4 Transform { 1.0f };

		// Constructors
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : Transform(transform) {}

		// glm::mat4 overloads
		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
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

		// Constructors
		SpriteRendererTextureComponent() = default;
		SpriteRendererTextureComponent(const SpriteRendererTextureComponent&) = default;
		SpriteRendererTextureComponent(const Ref<Texture2D> texture) : Texture(texture) {}
	};

	struct SpriteRendererSubTextureComponent
	{
		Hoowan::Ref<SubTexture2D> SubTexture;

		// Constructors
		SpriteRendererSubTextureComponent() = default;
		SpriteRendererSubTextureComponent(const SpriteRendererSubTextureComponent&) = default;
		SpriteRendererSubTextureComponent(const Ref<SubTexture2D> subTexture) : SubTexture(subTexture) {}
	};
}