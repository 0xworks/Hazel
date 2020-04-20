#pragma once

#include "Event.h"

namespace Hazel {

   class KeyEvent : public Event {
      EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
   public:
      uint32_t GetKeyCode() const;

   protected:
      KeyEvent(uint32_t keycode);
      uint32_t m_keyCode;
   };


   class KeyPressedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyPressed)
   public:
      KeyPressedEvent(uint32_t keycode, int repeatCount);

      int GetRepeatCount() const;

      std::string ToString() const override;

   protected:
      int m_repeatCount;
   };


   class KeyReleasedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyReleased)
   public:
      KeyReleasedEvent(uint32_t keycode);

      std::string ToString() const override;

   };


   class KeyTypedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyTyped)
   public:
      KeyTypedEvent(uint32_t keycode);

      std::string ToString() const override;

   };

}