#pragma once
#include "Event.h"

namespace Hazel {

   class MouseMovedEvent : public Event {
      EVENT_CLASS_TYPE(MouseMoved);
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      MouseMovedEvent(float x, float y);

      float GetX() const;
      float GetY() const;

      std::string ToString() const override;

   protected:
      float m_mouseX;
      float m_mouseY;
   };


   class MouseScrolledEvent : public Event {
      EVENT_CLASS_TYPE(MouseScrolled);
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

      float GetXOffset() const;
      float GetYOffset() const;

      std::string ToString() const override;

   private:
      float m_xOffset;
      float m_yOffset;
   };


   class MouseButtonEvent : public Event {
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      int GetMouseButton() const;

   protected:
      MouseButtonEvent(int button);
      int m_button;
   };


   class MouseButtonPressedEvent : public MouseButtonEvent {
      EVENT_CLASS_TYPE(MouseButtonPressed);
   public:
      MouseButtonPressedEvent(int button);

      std::string ToString() const override;

   };


   class MouseButtonReleasedEvent : public MouseButtonEvent {
      EVENT_CLASS_TYPE(MouseButtonReleased);
   public:
      MouseButtonReleasedEvent(int button);

      std::string ToString() const override;

   };

}
