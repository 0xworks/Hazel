#pragma once

#include "Hazel/Events/EventType.h"

#include <any>
#include <unordered_map>

namespace Hazel {

   class Event {
   public:
      Event() = delete;

      explicit Event(EventType type) : m_type(type) {}

      template<typename T>
      void SetParam(ParamId id, T value) {
         m_param[id] = value;
      }

      template<typename T>
      T GetParam(ParamId id) {
         return std::any_cast<T>(m_param[id]);
      }

      EventType GetType() const {
         return m_type;
      }

   private:
      EventType m_type {};
      std::unordered_map<ParamId, std::any> m_param;
   };

}
