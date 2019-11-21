#include "hzpch.h"
#include "Events/MouseEvent.h"
#include <sstream>

namespace Hazel {

   MouseMovedEvent::MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}


   float MouseMovedEvent::GetX() const {
      return m_mouseX;
   }


   float MouseMovedEvent::GetY() const {
      return m_mouseY;
   }


   std::string MouseMovedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
      return ss.str();
   }


   float MouseScrolledEvent::GetXOffset() const {
      return m_xOffset;
   }


   float MouseScrolledEvent::GetYOffset() const {
      return m_yOffset;
   }


   std::string MouseScrolledEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
      return ss.str();
   }


   MouseButtonEvent::MouseButtonEvent(int button) : m_button(button) {}


   int MouseButtonEvent::GetMouseButton() const {
      return m_button;
   }


   MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}


   std::string MouseButtonPressedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseButtonPressedEvent: " << m_button;
      return ss.str();
   }


   MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}


   std::string MouseButtonReleasedEvent::ToString() const {
      std::stringstream ss;
      ss << "MouseButtonReleasedEvent: " << m_button;
      return ss.str();
   }

}