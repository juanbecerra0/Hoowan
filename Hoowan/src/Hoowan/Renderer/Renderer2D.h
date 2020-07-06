#pragma once

#include "Hoowan/Renderer/OrthographicCamera.h"

namespace Hoowan {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primatives
		static void DrawQuad(const glm::vec2& position, const float rotation, const glm::vec3& size, const glm::vec4&color);
		static void DrawQuad(const glm::vec3& position, const float rotation, const glm::vec3& size, const glm::vec4& color);

	};
}