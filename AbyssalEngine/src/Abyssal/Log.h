#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Abyssal {
	class ABYSSAL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define ABYSSAL_CORE_TRACE(...)     ::Abyssal::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ABYSSAL_CORE_INFO(...)      ::Abyssal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ABYSSAL_CORE_WARN(...)      ::Abyssal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ABYSSAL_CORE_ERROR(...)     ::Abyssal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ABYSSAL_CORE_FATAL(...)     ::Abyssal::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Log Macros
#define ABYSSAL_TRACE(...)          ::Abyssal::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ABYSSAL_INFO(...)           ::Abyssal::Log::GetClientLogger()->info(__VA_ARGS__)
#define ABYSSAL_WARN(...)           ::Abyssal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ABYSSAL_ERROR(...)          ::Abyssal::Log::GetClientLogger()->error(__VA_ARGS__)
#define ABYSSAL_FATAL(...)          ::Abyssal::Log::GetClientLogger()->critical(__VA_ARGS__)