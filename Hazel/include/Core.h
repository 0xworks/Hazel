#pragma once

// #ifdef WIN32
// #ifdef Hazel_EXPORTS
// #define HAZEL_API __declspec(dllexport)
// #else
// #define HAZEL_API __declspec(dllimport)
// #endif
// #else
// #define HAZEL_API
// #endif
//#include <hazel_export.h>

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
