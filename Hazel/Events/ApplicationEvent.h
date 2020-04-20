#pragma once

#include "Event.h"

namespace Hazel {

   class WindowResizeEvent : public Event {
      EVENT_CLASS_TYPE(WindowResize);
      EVENT_CLASS_CATEGORY(EventCategoryApplication);
   public:
      WindowResizeEvent(uint32_t width, uint32_t height);

      uint32_t GetWidth() const;
      uint32_t GetHeight() const;

      std::string ToString() const override;

   private:
      uint32_t m_width;
      uint32_t m_height;
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