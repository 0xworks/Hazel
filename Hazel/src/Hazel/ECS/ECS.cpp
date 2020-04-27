#include "hzpch.h"
#include "Hazel/ECS/ECS.h"

namespace Hazel {

   namespace ECS {

      std::unique_ptr<EntityManager> entityManager;
      std::unique_ptr<ComponentManager> componentManager;
      std::unique_ptr<SystemManager> systemManager;

   }
}
