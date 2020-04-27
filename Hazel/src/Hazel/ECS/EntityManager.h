#pragma once

#include "Hazel/ECS/ECSType.h"

#include <array>
#include <queue>

namespace Hazel {

   namespace ECS {

      class EntityManager {
      public:
         EntityManager() {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
               m_entities.push(entity);
            }
         }

         Entity CreateEntity() {
            HZ_ASSERT(m_activeEntityCount < MAX_ENTITIES, "ERROR: Too many entities in existence.");
            Entity id = m_entities.front();
            m_entities.pop();
            ++m_activeEntityCount;
            return id;
         }

         void DestroyEntity(const Entity entity) {
            HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
            m_signatures[entity].reset();
            m_entities.push(entity);
            --m_activeEntityCount;
         }

         void SetSignature(const Entity entity, const Signature signature) {
            HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
            m_signatures[entity] = signature;
         }

         Signature GetSignature(const Entity entity) {
            HZ_CORE_ASSERT(entity < MAX_ENTITIES, "ERROR: Entity out of range.");
            return m_signatures[entity];
         }

      private:
         std::queue<Entity> m_entities;
         std::array<Signature, MAX_ENTITIES> m_signatures;
         uint32_t m_activeEntityCount = 0;
      };

   }
}