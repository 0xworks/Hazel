#pragma once

#include "Hazel/ECS/ECSType.h"

#include <set>

namespace Hazel {

   class System {
   friend class SystemManager;
   protected:
      std::set<Entity> m_entities;
   };

}
