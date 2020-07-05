#pragma once

#include <memory>

#ifdef HW_PLATFORM_WINDOWS
	#if HW_DYNAMIC_LINK
		#ifdef HW_BUILD_DLL
			#define HOOWAN_API __declspec(dllexport)
		#else
			#define HOOWAN_API __declspec(dllimport)
		#endif
	#else
		#define HOOWAN_API
	#endif
#else
	#error Hoowan only supports Windows!
#endif

#ifdef HW_DEBUG
	#define HW_ENABLE_ASSERTS
#endif

#ifdef HW_ENABLE_ASSERTS
	#define HW_ASSERT(x, ...) { if(!(x)) { HW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HW_CORE_ASSERT(x, ...) { if(!(x)) { HW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HW_ASSERT(x, ...)
	#define HW_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x) 

#define HW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hoowan {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}