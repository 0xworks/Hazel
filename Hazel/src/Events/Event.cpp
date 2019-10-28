#include "include/hzpch.h"
#include "Events/Event.h"

namespace Hazel {

   std::string Event::ToString() const {
      return GetName();
   }

   bool Event::IsInCategory(EventCategory category) {
      return GetCategoryFlags() & category;
   }

   EventDispatcher::EventDispatcher(Event& event) : m_Event(event) {

   }

}