#pragma once

#include "Hoowan/Renderer/OrthographicCamera.h"
#include "Hoowan/Renderer/Camera.h"
#include "Texture.h"
#include "SubTexture2D.h"

namespace Hoowan {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);	// TODO: remove when we fill out Camera API
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		static void Flush();

		// Colored quads 
		static void DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::mat4 transform, const glm::vec4& color);

		// Textured quads
		static void DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture);
	
		// Subtextured quad
		static void DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture);
		static void DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture);
		static void DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture);
		static void DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture);
		static void DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D> subTexture);

		// Statistics
		struct Stats
		{
			std::array<float, 100> FrameRenderTimes;
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t FrameCount = 0;

			float CurrentFrameBeginTime = 0.0f;
			float TotalFrameRenderTime = 0.0f;

			uint32_t GetDrawCallCount()			{ return DrawCalls; };
			uint32_t GetQuadCount()				{ return QuadCount; };
			uint32_t GetTriangleCount()			{ return QuadCount * 2; };
			uint32_t GetVertexCount()			{ return QuadCount * 4; };
			uint32_t GetIndexCount()			{ return QuadCount * 6; };

			
		};

		static Stats GetStats();
		static void ResetStats();

		static void StatsBeginFrame();
		static void StatsEndFrame();

	private:
		static void StartNewBatch();
	};
}