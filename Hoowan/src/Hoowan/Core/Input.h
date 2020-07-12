#pragma once

#include "Hoowan/Core/Core.h"
#include "Hoowan/Core/KeyCodes.h"
#include "Hoowan/Core/MouseCodes.h"

namespace Hoowan {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}