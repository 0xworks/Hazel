#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {

   std::shared_ptr<spdlog::logger> Log::s_spdlogCore;
   std::shared_ptr<spdlog::logger> Log::s_spdlogClient;

   void Log::Init() {
      spdlog::set_pattern("%^[%T] %n: %v%$");
      s_spdlogCore = spdlog::stdout_color_mt("HAZEL");
      s_spdlogCore->set_level(spdlog::level::trace);
      s_spdlogClient = spdlog::stdout_color_mt("APP");
      s_spdlogClient->set_level(spdlog::level::trace);
   }


   spdlog::logger& Log::GetCoreLogger() {
      return *s_spdlogCore;
   }

   spdlog::logger& Log::GetClientLogger() {
      return *s_spdlogClient;
   }

}
