#include "hwpch.h"
#include "SubTexture2D.h"

namespace Hoowan
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_Min = min;
		m_Max = max;

		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	void SubTexture2D::FlipOrientation(bool horizontal, bool vertical)
	{
		// Determine new min and max
		glm::vec2 newMin = { 0.0f, 0.0f };
		glm::vec2 newMax = { 0.0f, 0.0f };

		if (horizontal)
		{
			newMin.x = m_Min.x;
			newMax.x = m_Max.x;

			newMin.y = m_Max.y;
			newMax.y = m_Min.y;
		}
		else
		{
			newMin = m_Min;
			newMax = m_Max;
		}

		if (vertical)
		{
			newMin.x = m_Max.x;
			newMax.x = m_Min.x;
		}

		// Finally, reset texture coords
		m_TexCoords[0] = { newMin.x, newMin.y };
		m_TexCoords[1] = { newMax.x, newMin.y };
		m_TexCoords[2] = { newMax.x, newMax.y };
		m_TexCoords[3] = { newMin.x, newMax.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * cellSize.x) / texture->GetWidth(), (coords.y * cellSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		return CreateRef<SubTexture2D>(texture, min, max);
	}
}