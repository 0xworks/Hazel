#include "include/hzpch.h"
#include "Events/KeyEvent.h"
#include <sstream>

namespace Hazel {

   KeyEvent::KeyEvent(int keycode) : m_KeyCode(keycode) {}

   int Hazel::KeyEvent::GetKeyCode() const {
      return m_KeyCode;
   }


   KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}


   int KeyPressedEvent::GetRepeatCount() const {
      return m_RepeatCount;
   }


   std::string KeyPressedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
      return ss.str();
   }


   KeyReleasedEvent::KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}


   std::string KeyReleasedEvent::ToString() const {
      std::stringstream ss;
      ss << "KeyReleasedEvent: " << m_KeyCode;
      return ss.str();
   }

}