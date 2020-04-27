#pragma once

#include "Hazel/ECS/ECSType.h"

#include <array>
#include <unordered_map>

namespace Hazel {

   class IComponentArray {
   public:
      virtual ~IComponentArray() = default;
      virtual void EntityDestroyed(Entity entity) = 0;
   };


   template<typename T>
   class ComponentArray : public IComponentArray {
   public:
      void Insert(const Entity entity, T component) {
         HZ_CORE_ASSERT(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end(), "ERROR: Component added to same entity more than once.");

         // Put new entry at end
         size_t newIndex = m_size;
         m_entityToIndexMap[entity] = newIndex;
         m_indexToEntityMap[newIndex] = entity;
         m_componentArray[newIndex] = component;
         ++m_size;
      }


      void Remove(const Entity entity) {
         HZ_CORE_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "ERROR: Removing non-existent component.");

         // Copy element at end into deleted element's place to maintain density
         size_t indexOfRemovedEntity = m_entityToIndexMap[entity];
         size_t indexOfLastElement = m_size - 1;
         m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

         // Update map to point to moved spot
         Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
         m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
         m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

         m_entityToIndexMap.erase(entity);
         m_indexToEntityMap.erase(indexOfLastElement);

         --m_size;
      }


      T& Get(const Entity entity) {
         HZ_CORE_ASSERT(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(), "ERROR: Retrieving non-existent component.");
         return m_componentArray[m_entityToIndexMap[entity]];
      }


      void EntityDestroyed(const Entity entity) override {
         if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()) {
            Remove(entity);
         }
      }


   private:
      std::array<T, MAX_ENTITIES> m_componentArray;
      std::unordered_map<Entity, size_t> m_entityToIndexMap;
      std::unordered_map<size_t, Entity> m_indexToEntityMap;
      size_t m_size = 0;
   };

}
