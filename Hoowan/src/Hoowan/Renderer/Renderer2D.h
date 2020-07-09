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
		static void DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);

		static void DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
	
		// Statistics
		struct Stats
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetDrawCallCount()			{ return DrawCalls; };
			uint32_t GetQuadCount()				{ return QuadCount; };
			uint32_t GetTriangleCount()			{ return QuadCount * 2; };
			uint32_t GetVertexCount()			{ return QuadCount * 4; };
			uint32_t GetIndexCount()			{ return QuadCount * 6; };
		};

		static Stats GetStats();
		static void ResetStats();

	private:
		static void StartNewBatch();
	};
}