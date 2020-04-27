#pragma once

#include "Hazel/Events/EventManager.h"

namespace Hazel {

   namespace Events {
      std::unique_ptr<EventManager> eventManager;

      void AddEventListener(EventType eventType, std::function<void(Event&)> const& listener) {
         eventManager->AddListener(eventType, listener);
      }

      void SendEvent(Event& event) {
         eventManager->SendEvent(event);
      }

      void SendEvent(EventType eventType) {
         eventManager->SendEvent(eventType);
      }

   }

}