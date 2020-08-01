#include "hwpch.h"
#include "Hoowan/Physics/RectangleCollider.h"

namespace Hoowan
{

	// TODO: Account for rotated rectangle colliders using the transform component quaternion

	RectangleCollider::RectangleCollider(Ref<glm::mat4> transform)
		: m_Transform(transform), m_Dimensions({ 1.0f, 1.0f })
	{
		
	}

	RectangleCollider::RectangleCollider(Ref<glm::mat4> transform, const glm::vec2& dimensions)
		: m_Transform(transform), m_Dimensions(dimensions)
	{
		
	}

	bool RectangleCollider::IsColliding(RectangleCollider& other)
	{
		return AreColliding(*this, other);
	}

	bool RectangleCollider::AreColliding(RectangleCollider& rect1, RectangleCollider& rect2)
	{
		glm::vec2 rect1Origin = rect1.GetOrigin();
		glm::vec2 rect1Dimensions = rect1.GetDimensions();

		glm::vec2 rect2Origin = rect2.GetOrigin();
		glm::vec2 rect2Dimensions = rect2.GetDimensions();

		if (rect1Origin.x - (rect1Dimensions.x / 2) < rect2Origin.x + (rect2Dimensions.x / 2) &&
			rect1Origin.x + (rect1Dimensions.x / 2) > rect2Origin.x - (rect2Dimensions.x / 2) &&
			rect1Origin.y - (rect1Dimensions.y / 2) < rect2Origin.y + (rect2Dimensions.y / 2) &&
			rect1Origin.y + (rect1Dimensions.y / 2) > rect2Origin.y - (rect2Dimensions.y / 2))
			return true;

		return false;
	}

}