#pragma once

#include "Event.h"

namespace Hazel {

   class HAZEL_API KeyEvent : public Event {
      EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
   public:
      int GetKeyCode() const;

   protected:
      KeyEvent(int keycode);
      int m_KeyCode;
   };


   class HAZEL_API KeyPressedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyPressed)
   public:
      KeyPressedEvent(int keycode, int repeatCount);

      int GetRepeatCount() const;

      std::string ToString() const override;

   protected:
      int m_RepeatCount;
   };


   class HAZEL_API KeyReleasedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyReleased)
   public:
      KeyReleasedEvent(int keycode);

      std::string ToString() const override;

   };

}