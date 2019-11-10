#include "hzpch.h"
#include "Events/KeyEvent.h"
#include <sstream>

namespace Hazel {

   KeyEvent::KeyEvent(uint32_t keycode) : m_KeyCode(keycode) {}

   uint32_t Hazel::KeyEvent::GetKeyCode() const {
      return m_KeyCode;
   }


   KeyPressedEvent::KeyPressedEvent(uint32_t keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}


   int KeyPressedEvent::GetRepeatCount() const {
      return m_RepeatCount;
   }


   std::string KeyPressedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
      return ss.str();
   }


   KeyReleasedEvent::KeyReleasedEvent(uint32_t keycode) : KeyEvent(keycode) {}


   std::string KeyReleasedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << m_KeyCode;
      return ss.str();
   }


   KeyTypedEvent::KeyTypedEvent(uint32_t keycode) : KeyEvent(keycode) {}


   std::string KeyTypedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyTypedEvent: " << m_KeyCode;
      return ss.str();
   }
}