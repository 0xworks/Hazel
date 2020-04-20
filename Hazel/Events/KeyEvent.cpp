#include "hzpch.h"
#include "Events/KeyEvent.h"
#include <sstream>

namespace Hazel {

   KeyEvent::KeyEvent(uint32_t keycode) : m_keyCode(keycode) {}

   uint32_t Hazel::KeyEvent::GetKeyCode() const {
      return m_keyCode;
   }


   KeyPressedEvent::KeyPressedEvent(uint32_t keycode, int repeatCount) : KeyEvent(keycode), m_repeatCount(repeatCount) {}


   int KeyPressedEvent::GetRepeatCount() const {
      return m_repeatCount;
   }


   std::string KeyPressedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
      return ss.str();
   }


   KeyReleasedEvent::KeyReleasedEvent(uint32_t keycode) : KeyEvent(keycode) {}


   std::string KeyReleasedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << m_keyCode;
      return ss.str();
   }


   KeyTypedEvent::KeyTypedEvent(uint32_t keycode) : KeyEvent(keycode) {}


   std::string KeyTypedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyTypedEvent: " << m_keyCode;
      return ss.str();
   }
}