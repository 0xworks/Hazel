#pragma once

#ifdef WIN32
#ifdef Hazel_EXPORTS
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#define HAZEL_API
#endif

#define BIT(x) (1 << x)
