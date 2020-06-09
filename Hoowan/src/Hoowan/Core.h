#pragma once

#ifdef HW_PLATFORM_WINDOWS
	#ifdef HW_BUILD_DLL
		#define HOOWAN_API __declspec(dllexport)
	#else
		#define HOOWAN_API __declspec(dllimport)
	#endif
#else
	#error Hoowan only supports Windows!
#endif

#define BIT(x) (1 << x) 