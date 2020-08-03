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

	void RectangleCollider::SetPosition(const glm::vec2& newPosition)
	{
		(*m_Transform)[3][0] = newPosition.x;
		(*m_Transform)[3][1] = newPosition.y;
	}

	void RectangleCollider::CorrectCollision(RectangleCollider& dynamicRect, const RectangleCollider& staticRect, const glm::vec2& previousPosition)
	{
		// Get the distances between the adjacent edges of both colliders
		float left  =  ((staticRect.GetOrigin().x - (staticRect.GetDimensions().x / 2)) - (previousPosition.x + (dynamicRect.GetDimensions().x / 2)));
		float right =  ((previousPosition.x - (dynamicRect.GetDimensions().x / 2)) - (staticRect.GetOrigin().x + (staticRect.GetDimensions().x / 2)));
		float above =  ((previousPosition.y - (dynamicRect.GetDimensions().y / 2)) - (staticRect.GetOrigin().y + (staticRect.GetDimensions().y / 2)));
		float below =  ((staticRect.GetOrigin().y - (staticRect.GetDimensions().y / 2)) - (previousPosition.y + (dynamicRect.GetDimensions().y / 2)));

		// Determine the max of all of these values and push the dynamic rect in that direction
		if (left >= right)
		{
			if (above >= below)
			{
				if (left >= above)
				{
					// Left
					HW_CORE_INFO("LEFT");
					dynamicRect.SetPosition({ staticRect.GetOrigin().x - (staticRect.GetDimensions().x / 2) - (dynamicRect.GetDimensions().x / 2), 
						dynamicRect.GetOrigin().y });
				}
				else
				{
					// Above
					HW_CORE_INFO("ABOVE");
					dynamicRect.SetPosition({ dynamicRect.GetOrigin().x, 
						staticRect.GetOrigin().y + (staticRect.GetDimensions().y / 2) + (dynamicRect.GetDimensions().y / 2) });
				}
			}
			else
			{
				if (left >= below)
				{
					// Left
					HW_CORE_INFO("LEFT");
					dynamicRect.SetPosition({ staticRect.GetOrigin().x - (staticRect.GetDimensions().x / 2) - (dynamicRect.GetDimensions().x / 2), 
						dynamicRect.GetOrigin().y });
				}
				else
				{
					// Below
					HW_CORE_INFO("BELOW");
					dynamicRect.SetPosition({ dynamicRect.GetOrigin().x, 
						staticRect.GetOrigin().y - (staticRect.GetDimensions().y / 2) - (dynamicRect.GetDimensions().y / 2) });
				}
			}
		}
		else
		{
			if (above >= below)
			{
				if (right >= above)
				{
					// Right
					HW_CORE_INFO("RIGHT");
					dynamicRect.SetPosition({ staticRect.GetOrigin().x + (staticRect.GetDimensions().x / 2) + (dynamicRect.GetDimensions().x / 2),
						dynamicRect.GetOrigin().y });
				}
				else
				{
					// Above
					HW_CORE_INFO("ABOVE");
					dynamicRect.SetPosition({ dynamicRect.GetOrigin().x, 
						staticRect.GetOrigin().y + (staticRect.GetDimensions().y / 2) + (dynamicRect.GetDimensions().y / 2) });
				}
			}
			else
			{
				if (right >= below)
				{
					// Right
					HW_CORE_INFO("RIGHT");
					dynamicRect.SetPosition({ staticRect.GetOrigin().x + (staticRect.GetDimensions().x / 2) + (dynamicRect.GetDimensions().x / 2),
						dynamicRect.GetOrigin().y });
				}
				else
				{
					// Below
					HW_CORE_INFO("BELOW");
					dynamicRect.SetPosition({ dynamicRect.GetOrigin().x, 
						staticRect.GetOrigin().y - (staticRect.GetDimensions().y / 2) - (dynamicRect.GetDimensions().y / 2) });
				}
			}
		}

 	}

}