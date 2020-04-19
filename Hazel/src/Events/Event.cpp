#include "hzpch.h"
#include "Events/Event.h"

namespace Hazel {

   std::string Event::ToString() const {
      return GetName();
   }


   bool Event::IsInCategory(EventCategory category) {
      return GetCategoryFlags() & category;
   }


   bool Event::IsHandled() {
      return m_handled;
   }


   EventDispatcher::EventDispatcher(Event& event) : m_event(event) {}

}