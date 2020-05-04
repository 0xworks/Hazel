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

#include "Hazel/Core/Log.h"

#ifdef HZ_DEBUG
#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR(__VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif
