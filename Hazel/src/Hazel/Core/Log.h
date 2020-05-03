#pragma once

#include <spdlog/spdlog.h>

namespace Hazel {

	class Log {
	public:

		static void Init();

		static spdlog::logger& GetCoreLogger();
		static spdlog::logger& GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_spdlogCore;
		static std::shared_ptr<spdlog::logger> s_spdlogClient;
	};

}

#define HZ_CORE_TRACE(...)   ::Hazel::Log::GetCoreLogger().trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)    ::Hazel::Log::GetCoreLogger().info(__VA_ARGS__)
#define HZ_CORE_WARN(...)    ::Hazel::Log::GetCoreLogger().warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)   ::Hazel::Log::GetCoreLogger().error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)   ::Hazel::Log::GetCoreLogger().critical(__VA_ARGS__)

#define HZ_TRACE(...)        ::Hazel::Log::GetClientLogger().trace(__VA_ARGS__)
#define HZ_INFO(...)         ::Hazel::Log::GetClientLogger().info(__VA_ARGS__)
#define HZ_WARN(...)         ::Hazel::Log::GetClientLogger().warn(__VA_ARGS__)
#define HZ_ERROR(...)        ::Hazel::Log::GetClientLogger().error(__VA_ARGS__)
#define HZ_FATAL(...)        ::Hazel::Log::GetClientLogger().critical(__VA_ARGS__)
