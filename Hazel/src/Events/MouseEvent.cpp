#include "include/hzpch.h"
#include "Events/MouseEvent.h"
#include <sstream>

namespace Hazel {

   MouseMovedEvent::MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}


   float MouseMovedEvent::GetX() const {
      return m_MouseX;
   }


   float MouseMovedEvent::GetY() const {
      return m_MouseY;
   }


   std::string MouseMovedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
      return ss.str();
   }


   float MouseScrolledEvent::GetXOffset() const {
      return m_XOffset;
   }


   float MouseScrolledEvent::GetYOffset() const {
      return m_YOffset;
   }


   std::string MouseScrolledEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
      return ss.str();
   }


   MouseButtonEvent::MouseButtonEvent(int button) : m_Button(button) {}


   int MouseButtonEvent::GetMouseButton() const {
      return m_Button;
   }


   MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}


   std::string MouseButtonPressedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseButtonPressedEvent: " << m_Button;
      return ss.str();
   }


   MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}


   std::string MouseButtonReleasedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent: " << m_Button;
      return ss.str();
   }

}