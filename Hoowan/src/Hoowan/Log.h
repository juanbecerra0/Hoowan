#pragma once
#include "hwpch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hoowan {
	class HOOWAN_API Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

// Core logging macros
#define HW_CORE_TRACE(...)	::Hoowan::Log::GetCoreLogger() ->trace		(__VA_ARGS__)
#define HW_CORE_INFO(...)	::Hoowan::Log::GetCoreLogger() ->info		(__VA_ARGS__)
#define HW_CORE_WARN(...)	::Hoowan::Log::GetCoreLogger() ->warn		(__VA_ARGS__)
#define HW_CORE_ERROR(...)	::Hoowan::Log::GetCoreLogger() ->error		(__VA_ARGS__)
#define HW_CORE_FATAL(...)	::Hoowan::Log::GetCoreLogger() ->critical	(__VA_ARGS__)


// Client logging macros
#define HW_TRACE(...)	::Hoowan::Log::GetClientLogger() ->trace	(__VA_ARGS__)
#define HW_INFO(...)	::Hoowan::Log::GetClientLogger() ->info		(__VA_ARGS__)
#define HW_WARN(...)	::Hoowan::Log::GetClientLogger() ->warn		(__VA_ARGS__)
#define HW_ERROR(...)	::Hoowan::Log::GetClientLogger() ->error	(__VA_ARGS__)
#define HW_FATAL(...)	::Hoowan::Log::GetClientLogger() ->critical	(__VA_ARGS__)