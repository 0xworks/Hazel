#pragma once

#include "Event.h"

namespace Hazel {

   class KeyEvent : public Event {
      EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
   public:
      int GetKeyCode() const;

   protected:
      KeyEvent(int keycode);
      int m_KeyCode;
   };


   class KeyPressedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyPressed)
   public:
      KeyPressedEvent(int keycode, int repeatCount);

      int GetRepeatCount() const;

      std::string ToString() const override;

   protected:
      int m_RepeatCount;
   };


   class KeyReleasedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyReleased)
   public:
      KeyReleasedEvent(int keycode);

      std::string ToString() const override;

   };


   class KeyTypedEvent : public KeyEvent {
      EVENT_CLASS_TYPE(KeyTyped)
   public:
      KeyTypedEvent(int keycode);

      std::string ToString() const override;

   };

}