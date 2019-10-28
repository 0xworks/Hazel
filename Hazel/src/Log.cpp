#include "include/hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {

   std::shared_ptr<spdlog::logger> Log::s_spdCoreLogger;
   std::shared_ptr<spdlog::logger> Log::s_spdClientLogger;

   void Log::Init() {
      spdlog::set_pattern("%^[%T] %n: %v%$");
      s_spdCoreLogger = spdlog::stdout_color_mt("HAZEL");
      s_spdCoreLogger->set_level(spdlog::level::trace);
      s_spdClientLogger = spdlog::stdout_color_mt("APP");
      s_spdClientLogger->set_level(spdlog::level::trace);
   }


}
