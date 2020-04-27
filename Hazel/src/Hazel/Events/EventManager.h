#pragma once

#include "Hazel/Events/Event.h"

#include <functional>
#include <list>
#include <unordered_map>

namespace Hazel {

   class EventManager {
   public:
      void AddListener(EventType eventType, std::function<void(Event&)> const& listener) {
         m_listeners[eventType].push_back(listener);
      }

      void SendEvent(Event& event) {
         for (auto const& listener : m_listeners[event.GetType()]) {
            listener(event);
         }
      }

      void SendEvent(EventType eventType) {
         Event event(eventType);
         for (auto const& listener : m_listeners[eventType]) {
            listener(event);
         }
      }

   private:
      std::unordered_map<EventType, std::list<std::function<void(Event&)>>> m_listeners;
   };

}
