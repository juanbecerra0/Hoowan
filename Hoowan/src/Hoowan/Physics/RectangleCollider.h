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
		void SetPosition(const glm::vec2& newPosition);
		glm::vec2 GetDimensions() const { return m_Dimensions; }
		glm::vec2 GetOrigin() const { return (*m_Transform)[3]; }

		bool IsColliding(RectangleCollider& other);
		static bool AreColliding(RectangleCollider& rect1, RectangleCollider& rect2);

		static void CorrectCollision(RectangleCollider& dynamicRect, const RectangleCollider& staticRect, const glm::vec2& previousPosition);

	private:
		Ref<glm::mat4> m_Transform;
		glm::vec2 m_Dimensions;
	};
}