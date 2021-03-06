#include "hwpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include <glm\ext\matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace Hoowan
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 8192;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;	// TODO: get rendering API cap

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;	// 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Stats stats;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		HW_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		// Set up vertex buffer
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"	},
			{ ShaderDataType::Float4,	"a_Color"		},
			{ ShaderDataType::Float2,	"a_TexCoord"	},
			{ ShaderDataType::Float,	"a_TexIndex"	}
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		// Set up index buffer
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> squareIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(squareIB);
		delete[] quadIndices;

		// Set up blank texture
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (int32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		// Compile Shaders
		s_Data.Shader = Shader::Create("assets/shaders/Sprite.glsl");
		s_Data.Shader->Bind();
		s_Data.Shader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		// Construct vertex location of quad
		s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		HW_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HW_PROFILE_FUNCTION();

		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		HW_PROFILE_FUNCTION();

		glm::mat4 viewProjection = camera.GetProjection() * glm::inverse(transform);

		s_Data.Shader->Bind();
		s_Data.Shader->SetMat4("u_ViewProjection", viewProjection);

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		HW_PROFILE_FUNCTION();

		// Size needs to be casted down to something that is one byte to get element numbers
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		// Bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		// Bind indices
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.stats.DrawCalls++;
	}

	void Renderer2D::StartNewBatch()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// Colored quads
	// ----------------------------------------------------------------------------------------------------------------

	void Renderer2D::DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawStaticQuad({ translation.x, translation.y, 0.0f}, scale, color);
	}

	void Renderer2D::DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const glm::vec4& color)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawRotatedQuad({ translation.x, translation.y, 0.0f }, rotation, scale, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4 transform, const glm::vec4& color)
	{
		HW_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			StartNewBatch();

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = 0;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		s_Data.WhiteTexture->Bind();

		s_Data.stats.QuadCount++;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// Textured quads
	// ----------------------------------------------------------------------------------------------------------------

	void Renderer2D::DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const Ref<Texture2D> texture)
	{
		DrawStaticQuad({ translation.x, translation.y, 0.0f }, scale, texture);
	}

	void Renderer2D::DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const Ref<Texture2D> texture)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture)
	{
		DrawRotatedQuad({ translation.x, translation.y, 0.0f }, rotation, scale, texture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<Texture2D> texture)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, texture);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture)
	{
		HW_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			StartNewBatch();

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		s_Data.WhiteTexture->Bind();

		s_Data.stats.QuadCount++;
	}

	// ----------------------------------------------------------------------------------------------------------------
	// Subtextured quads
	// ----------------------------------------------------------------------------------------------------------------

	void Renderer2D::DrawStaticQuad(const glm::vec2& translation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture)
	{
		DrawStaticQuad({ translation.x, translation.y, 0.0f }, scale, subTexture);
	}

	void Renderer2D::DrawStaticQuad(const glm::vec3& translation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, subTexture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture)
	{
		DrawRotatedQuad({ translation.x, translation.y, 0.0f }, rotation, scale, subTexture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const Ref<SubTexture2D>& subTexture)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), translation) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		DrawQuad(transform, subTexture);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<SubTexture2D> subTexture)
	{
		HW_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			StartNewBatch();

		float textureIndex = 0.0f;

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *subTexture->GetTexture().get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = subTexture->GetTexture();
			s_Data.TextureSlotIndex++;
		}

		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		const glm::vec2* texCoords = subTexture->GetTexCoords();

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = texCoords[0];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = texCoords[1];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = texCoords[2];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = texCoords[3];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		s_Data.stats.QuadCount++;
	}

	Hoowan::Renderer2D::Stats Renderer2D::GetStats()
	{
		return s_Data.stats;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.stats, 0, sizeof(Stats));
	}

	void Renderer2D::StatsBeginFrame()
	{
		s_Data.stats.CurrentFrameBeginTime = (float)glfwGetTime();
	}

	void Renderer2D::StatsEndFrame()
	{
		s_Data.stats.FrameRenderTimes[s_Data.stats.FrameCount] = (float)glfwGetTime() - s_Data.stats.CurrentFrameBeginTime;
		s_Data.stats.TotalFrameRenderTime += (s_Data.stats.FrameRenderTimes[s_Data.stats.FrameCount] - s_Data.stats.FrameRenderTimes[(s_Data.stats.FrameCount + 1) % s_Data.stats.FrameRenderTimes.size()]);

		if (++s_Data.stats.FrameCount == s_Data.stats.FrameRenderTimes.size())
			s_Data.stats.FrameCount = 0;
	}
}