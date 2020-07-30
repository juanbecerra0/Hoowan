#pragma once

#include "glm/glm.hpp"

namespace Hoowan
{
	class RectangleCollider
	{
	public:
		RectangleCollider(Ref<glm::mat4> transform);
		RectangleCollider(Ref<glm::mat4> transform, const glm::vec2& dimensions);

		void SetDimensions(const glm::vec2& dimensions) { m_Dimensions = dimensions; }
		glm::vec2 GetDimensions() { return m_Dimensions; }
		glm::vec2 GetOrigin() { return (*m_Transform)[3]; }

		bool IsColliding(RectangleCollider& other);
		static bool AreColliding(RectangleCollider& rect1, RectangleCollider& rect2);

	private:
		Ref<glm::mat4> m_Transform;
		glm::vec2 m_Dimensions;
	};
}