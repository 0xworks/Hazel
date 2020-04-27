#pragma  once

#include "Hazel/ECS/ComponentArray.h"

#include <memory>
#include <unordered_map>

namespace Hazel {

   class ComponentManager {
   public:
      template<typename T>
      void RegisterComponent() {
         const char* typeName = typeid(T).name();
         HZ_CORE_ASSERT(m_componentTypes.find(typeName) == m_componentTypes.end(), "ERROR: Registering component type '{}' more than once.", typeName);
         m_componentTypes.insert({typeName, m_nextComponentType});
         m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
         ++m_nextComponentType;
      }

      template<typename T>
      ComponentType GetComponentType() {
         const char* typeName = typeid(T).name();
         HZ_CORE_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "ERROR: Component type '{}' not registered before use.", typeName);
         return m_componentTypes[typeName];
      }

      template<typename T>
      void AddComponent(const Entity entity, T component) {
         GetComponentArray<T>()->Insert(entity, component);
      }

      template<typename T>
      void RemoveComponent(const Entity entity) {
         GetComponentArray<T>()->Remove(entity);
      }

      template<typename T>
      T& GetComponent(const Entity entity) {
         return GetComponentArray<T>()->Get(entity);
      }

      void EntityDestroyed(const Entity entity) {
         for (auto const& [name, component] : m_componentArrays) {
            component->EntityDestroyed(entity);
         }
      }

   private:
      std::unordered_map<const char*, ComponentType> m_componentTypes;
      std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;
      ComponentType m_nextComponentType = 0;

      template<typename T>
      std::shared_ptr<ComponentArray<T>> GetComponentArray() {
         const char* typeName = typeid(T).name();
         HZ_CORE_ASSERT(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");
         return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
      }

   };

}
