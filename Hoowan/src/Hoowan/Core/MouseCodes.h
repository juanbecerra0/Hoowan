#pragma once

namespace Hoowan
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define HW_MOUSE_BUTTON_0      ::Hoowan::Mouse::Button0
#define HW_MOUSE_BUTTON_1      ::Hoowan::Mouse::Button1
#define HW_MOUSE_BUTTON_2      ::Hoowan::Mouse::Button2
#define HW_MOUSE_BUTTON_3      ::Hoowan::Mouse::Button3
#define HW_MOUSE_BUTTON_4      ::Hoowan::Mouse::Button4
#define HW_MOUSE_BUTTON_5      ::Hoowan::Mouse::Button5
#define HW_MOUSE_BUTTON_6      ::Hoowan::Mouse::Button6
#define HW_MOUSE_BUTTON_7      ::Hoowan::Mouse::Button7
#define HW_MOUSE_BUTTON_LAST   ::Hoowan::Mouse::ButtonLast
#define HW_MOUSE_BUTTON_LEFT   ::Hoowan::Mouse::ButtonLeft
#define HW_MOUSE_BUTTON_RIGHT  ::Hoowan::Mouse::ButtonRight
#define HW_MOUSE_BUTTON_MIDDLE ::Hoowan::Mouse::ButtonMiddle