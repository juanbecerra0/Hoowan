#pragma once

namespace Hoowan
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HW_KEY_SPACE           ::Hoowan::Key::Space
#define HW_KEY_APOSTROPHE      ::Hoowan::Key::Apostrophe    /* ' */
#define HW_KEY_COMMA           ::Hoowan::Key::Comma         /* , */
#define HW_KEY_MINUS           ::Hoowan::Key::Minus         /* - */
#define HW_KEY_PERIOD          ::Hoowan::Key::Period        /* . */
#define HW_KEY_SLASH           ::Hoowan::Key::Slash         /* / */
#define HW_KEY_0               ::Hoowan::Key::D0
#define HW_KEY_1               ::Hoowan::Key::D1
#define HW_KEY_2               ::Hoowan::Key::D2
#define HW_KEY_3               ::Hoowan::Key::D3
#define HW_KEY_4               ::Hoowan::Key::D4
#define HW_KEY_5               ::Hoowan::Key::D5
#define HW_KEY_6               ::Hoowan::Key::D6
#define HW_KEY_7               ::Hoowan::Key::D7
#define HW_KEY_8               ::Hoowan::Key::D8
#define HW_KEY_9               ::Hoowan::Key::D9
#define HW_KEY_SEMICOLON       ::Hoowan::Key::Semicolon     /* ; */
#define HW_KEY_EQUAL           ::Hoowan::Key::Equal         /* = */
#define HW_KEY_A               ::Hoowan::Key::A
#define HW_KEY_B               ::Hoowan::Key::B
#define HW_KEY_C               ::Hoowan::Key::C
#define HW_KEY_D               ::Hoowan::Key::D
#define HW_KEY_E               ::Hoowan::Key::E
#define HW_KEY_F               ::Hoowan::Key::F
#define HW_KEY_G               ::Hoowan::Key::G
#define HW_KEY_H               ::Hoowan::Key::H
#define HW_KEY_I               ::Hoowan::Key::I
#define HW_KEY_J               ::Hoowan::Key::J
#define HW_KEY_K               ::Hoowan::Key::K
#define HW_KEY_L               ::Hoowan::Key::L
#define HW_KEY_M               ::Hoowan::Key::M
#define HW_KEY_N               ::Hoowan::Key::N
#define HW_KEY_O               ::Hoowan::Key::O
#define HW_KEY_P               ::Hoowan::Key::P
#define HW_KEY_Q               ::Hoowan::Key::Q
#define HW_KEY_R               ::Hoowan::Key::R
#define HW_KEY_S               ::Hoowan::Key::S
#define HW_KEY_T               ::Hoowan::Key::T
#define HW_KEY_U               ::Hoowan::Key::U
#define HW_KEY_V               ::Hoowan::Key::V
#define HW_KEY_W               ::Hoowan::Key::W
#define HW_KEY_X               ::Hoowan::Key::X
#define HW_KEY_Y               ::Hoowan::Key::Y
#define HW_KEY_Z               ::Hoowan::Key::Z
#define HW_KEY_LEFT_BRACKET    ::Hoowan::Key::LeftBracket   /* [ */
#define HW_KEY_BACKSLASH       ::Hoowan::Key::Backslash     /* \ */
#define HW_KEY_RIGHT_BRACKET   ::Hoowan::Key::RightBracket  /* ] */
#define HW_KEY_GRAVE_ACCENT    ::Hoowan::Key::GraveAccent   /* ` */
#define HW_KEY_WORLD_1         ::Hoowan::Key::World1        /* non-US #1 */
#define HW_KEY_WORLD_2         ::Hoowan::Key::World2        /* non-US #2 */

/* Function keys */
#define HW_KEY_ESCAPE          ::Hoowan::Key::Escape
#define HW_KEY_ENTER           ::Hoowan::Key::Enter
#define HW_KEY_TAB             ::Hoowan::Key::Tab
#define HW_KEY_BACKSPACE       ::Hoowan::Key::Backspace
#define HW_KEY_INSERT          ::Hoowan::Key::Insert
#define HW_KEY_DELETE          ::Hoowan::Key::Delete
#define HW_KEY_RIGHT           ::Hoowan::Key::Right
#define HW_KEY_LEFT            ::Hoowan::Key::Left
#define HW_KEY_DOWN            ::Hoowan::Key::Down
#define HW_KEY_UP              ::Hoowan::Key::Up
#define HW_KEY_PAGE_UP         ::Hoowan::Key::PageUp
#define HW_KEY_PAGE_DOWN       ::Hoowan::Key::PageDown
#define HW_KEY_HOME            ::Hoowan::Key::Home
#define HW_KEY_END             ::Hoowan::Key::End
#define HW_KEY_CAPS_LOCK       ::Hoowan::Key::CapsLock
#define HW_KEY_SCROLL_LOCK     ::Hoowan::Key::ScrollLock
#define HW_KEY_NUM_LOCK        ::Hoowan::Key::NumLock
#define HW_KEY_PRINT_SCREEN    ::Hoowan::Key::PrintScreen
#define HW_KEY_PAUSE           ::Hoowan::Key::Pause
#define HW_KEY_F1              ::Hoowan::Key::F1
#define HW_KEY_F2              ::Hoowan::Key::F2
#define HW_KEY_F3              ::Hoowan::Key::F3
#define HW_KEY_F4              ::Hoowan::Key::F4
#define HW_KEY_F5              ::Hoowan::Key::F5
#define HW_KEY_F6              ::Hoowan::Key::F6
#define HW_KEY_F7              ::Hoowan::Key::F7
#define HW_KEY_F8              ::Hoowan::Key::F8
#define HW_KEY_F9              ::Hoowan::Key::F9
#define HW_KEY_F10             ::Hoowan::Key::F10
#define HW_KEY_F11             ::Hoowan::Key::F11
#define HW_KEY_F12             ::Hoowan::Key::F12
#define HW_KEY_F13             ::Hoowan::Key::F13
#define HW_KEY_F14             ::Hoowan::Key::F14
#define HW_KEY_F15             ::Hoowan::Key::F15
#define HW_KEY_F16             ::Hoowan::Key::F16
#define HW_KEY_F17             ::Hoowan::Key::F17
#define HW_KEY_F18             ::Hoowan::Key::F18
#define HW_KEY_F19             ::Hoowan::Key::F19
#define HW_KEY_F20             ::Hoowan::Key::F20
#define HW_KEY_F21             ::Hoowan::Key::F21
#define HW_KEY_F22             ::Hoowan::Key::F22
#define HW_KEY_F23             ::Hoowan::Key::F23
#define HW_KEY_F24             ::Hoowan::Key::F24
#define HW_KEY_F25             ::Hoowan::Key::F25

/* Keypad */
#define HW_KEY_KP_0            ::Hoowan::Key::KP0
#define HW_KEY_KP_1            ::Hoowan::Key::KP1
#define HW_KEY_KP_2            ::Hoowan::Key::KP2
#define HW_KEY_KP_3            ::Hoowan::Key::KP3
#define HW_KEY_KP_4            ::Hoowan::Key::KP4
#define HW_KEY_KP_5            ::Hoowan::Key::KP5
#define HW_KEY_KP_6            ::Hoowan::Key::KP6
#define HW_KEY_KP_7            ::Hoowan::Key::KP7
#define HW_KEY_KP_8            ::Hoowan::Key::KP8
#define HW_KEY_KP_9            ::Hoowan::Key::KP9
#define HW_KEY_KP_DECIMAL      ::Hoowan::Key::KPDecimal
#define HW_KEY_KP_DIVIDE       ::Hoowan::Key::KPDivide
#define HW_KEY_KP_MULTIPLY     ::Hoowan::Key::KPMultiply
#define HW_KEY_KP_SUBTRACT     ::Hoowan::Key::KPSubtract
#define HW_KEY_KP_ADD          ::Hoowan::Key::KPAdd
#define HW_KEY_KP_ENTER        ::Hoowan::Key::KPEnter
#define HW_KEY_KP_EQUAL        ::Hoowan::Key::KPEqual

#define HW_KEY_LEFT_SHIFT      ::Hoowan::Key::LeftShift
#define HW_KEY_LEFT_CONTROL    ::Hoowan::Key::LeftControl
#define HW_KEY_LEFT_ALT        ::Hoowan::Key::LeftAlt
#define HW_KEY_LEFT_SUPER      ::Hoowan::Key::LeftSuper
#define HW_KEY_RIGHT_SHIFT     ::Hoowan::Key::RightShift
#define HW_KEY_RIGHT_CONTROL   ::Hoowan::Key::RightControl
#define HW_KEY_RIGHT_ALT       ::Hoowan::Key::RightAlt
#define HW_KEY_RIGHT_SUPER     ::Hoowan::Key::RightSuper
#define HW_KEY_MENU            ::Hoowan::Key::Menu