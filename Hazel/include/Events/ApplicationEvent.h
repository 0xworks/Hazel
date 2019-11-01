#pragma once

#include "Event.h"

namespace Hazel {

   class WindowResizeEvent : public Event {
      EVENT_CLASS_TYPE(WindowResize);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      WindowResizeEvent(unsigned int width, unsigned int height);

      unsigned int GetWidth() const;
      unsigned int GetHeight() const;

      std::string ToString() const override;

   private:
      unsigned int m_Width, m_Height;
   };


   class WindowCloseEvent : public Event {
      EVENT_CLASS_TYPE(WindowClose);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      WindowCloseEvent();
   };


   class AppTickEvent : public Event {
      EVENT_CLASS_TYPE(AppTick);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      AppTickEvent();
   };


   class AppUpdateEvent : public Event {
      EVENT_CLASS_TYPE(AppUpdate);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      AppUpdateEvent();
   };


   class AppRenderEvent : public Event {
      EVENT_CLASS_TYPE(AppRender);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      AppRenderEvent();
   };

}