#pragma once

#include "Hazel/ECS/System.h"

#include <memory>
#include <unordered_map>

namespace Hazel {

   class SystemManager {
   public:
      template<typename T>
      std::shared_ptr<T> RegisterSystem() {
         const char* typeName = typeid(T).name();
         HZ_CORE_ASSERT(m_systems.find(typeName) == m_systems.end(), "ERROR: Registering system '{}' more than once.", typeName);
         auto system = std::make_shared<T>();
         m_systems.insert({typeName, system});
         return system;
      }

      template<typename T>
      void SetSignature(const Signature signature) {
         const char* typeName = typeid(T).name();
         HZ_CORE_ASSERT(m_systems.find(typeName) != m_systems.end() && "ERROR: System '{}' used before registered.", typeName);
         m_signatures.insert({typeName, signature});
      }

      void EntityDestroyed(const Entity entity) {
         for (auto const& pair : m_systems) {
            auto const& system = pair.second;
            system->m_entities.erase(entity);
         }
      }

      void EntitySignatureChanged(const Entity entity, const Signature entitySignature) {
         for (auto const& [type, system] : m_systems) {
            auto const& systemSignature = m_signatures[type];
            if ((entitySignature & systemSignature) == systemSignature) {
               system->m_entities.insert(entity);
            } else {
               system->m_entities.erase(entity);
            }
         }
      }

   private:
      std::unordered_map<const char*, Signature> m_signatures;
      std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
   };

}