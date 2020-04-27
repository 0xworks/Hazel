#pragma once

#include "Hazel/Events/EventManager.h"

namespace Hazel {

   namespace Events {

      extern std::unique_ptr<EventManager> eventManager;

      inline void AddEventListener(EventType eventType, std::function<void(Event&)> const& listener) {
         eventManager->AddListener(eventType, listener);
      }

      inline void SendEvent(Event& event) {
         eventManager->SendEvent(event);
      }

      inline void SendEvent(EventType eventType) {
         eventManager->SendEvent(eventType);
      }

   }

}