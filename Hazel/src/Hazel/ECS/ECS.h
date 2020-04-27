#pragma once

#include "Hazel/ECS/EntityManager.h"
#include "Hazel/ECS/ComponentManager.h"
#include "Hazel/ECS/SystemManager.h"

namespace Hazel {

   namespace ECS {
      std::unique_ptr<EntityManager> entityManager;
      std::unique_ptr<ComponentManager> componentManager;
      std::unique_ptr<SystemManager> systemManager;


      Entity CreateEntity() {
         return entityManager->CreateEntity();
      }

      void DestroyEntity(const Entity entity) {
         entityManager->DestroyEntity(entity);
         componentManager->EntityDestroyed(entity);
         systemManager->EntityDestroyed(entity);
      }


      template<typename T>
      void RegisterComponent() {
         componentManager->RegisterComponent<T>();
      }

      template<typename T>
      void AddComponent(const Entity entity, T component) {
         componentManager->AddComponent<T>(entity, component);
         auto signature = entityManager->GetSignature(entity);
         signature.set(componentManager->GetComponentType<T>(), true);
         entityManager->SetSignature(entity, signature);
         systemManager->EntitySignatureChanged(entity, signature);
      }

      template<typename T>
      void RemoveComponent(const Entity entity) {
         componentManager->RemoveComponent<T>(entity);
         auto signature = entityManager->GetSignature(entity);
         signature.set(m_componentManager->GetComponentType<T>(), false);
         entityManager->SetSignature(entity, signature);
         systemManager->EntitySignatureChanged(entity, signature);
      }

      template<typename T>
      T& GetComponent(const Entity entity) {
         return componentManager->GetComponent<T>(entity);
      }

      template<typename T>
      ComponentType GetComponentType() {
         return componentManager->GetComponentType<T>();
      }


      template<typename T>
      std::shared_ptr<T> RegisterSystem() {
         return systemManager->RegisterSystem<T>();
      }

      template<typename T>
      void SetSystemSignature(const Signature signature) {
         systemManager->SetSignature<T>(signature);
      }

   }

}