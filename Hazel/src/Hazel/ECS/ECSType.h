#pragma once

#include <bitset>

namespace Hazel {

	namespace ECS {

		using Entity = uint32_t;
		const Entity MAX_ENTITIES = 15000;
		using ComponentType = uint8_t;
		const ComponentType MAX_COMPONENTS = 32;
		using Signature = std::bitset<MAX_COMPONENTS>;

	}
}
