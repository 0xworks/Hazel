#pragma once
#include "Event.h"

namespace Hazel {

   class HAZEL_API MouseMovedEvent : public Event {
      EVENT_CLASS_TYPE(MouseMoved);
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      MouseMovedEvent(float x, float y);

      float GetX() const;
      float GetY() const;

      std::string ToString() const override;

   protected:
      float m_MouseX;
      float m_MouseY;
   };


   class HAZEL_API MouseScrolledEvent : public Event {
      EVENT_CLASS_TYPE(MouseScrolled);
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

      float GetXOffset() const;
      float GetYOffset() const;

      std::string ToString() const override;

   private:
      float m_XOffset;
      float m_YOffset;
   };


   class HAZEL_API MouseButtonEvent : public Event {
      EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
   public:
      int GetMouseButton() const;

   protected:
      MouseButtonEvent(int button);
      int m_Button;
   };


   class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
      EVENT_CLASS_TYPE(MouseButtonPressed);
   public:
      MouseButtonPressedEvent(int button);

      std::string ToString() const override;

   };


   class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
      EVENT_CLASS_TYPE(MouseButtonReleased);
   public:
      MouseButtonReleasedEvent(int button);

      std::string ToString() const override;

   };

}
