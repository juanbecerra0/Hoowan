#pragma once

#include "Hoowan/Renderer/OrthographicCamera.h"
#include "Texture.h"

namespace Hoowan {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primatives
		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4&color);
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
	};
}