#pragma once

#include <cstddef>
#include <cstdint>

// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count) {
	return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, size_t count) {
	return fnv1a_32(s, count);
}

namespace Hazel {

	using EventType = std::uint32_t;
	using ParamId = std::uint32_t;


}

#define HZ_BIND_EVENT_METHOD(event, method) event, std::bind(&method, this, std::placeholders::_1)
#define HZ_BIND_EVENT_FUNCTION(event, function) event, std::bind(&function, std::placeholders::_1)
