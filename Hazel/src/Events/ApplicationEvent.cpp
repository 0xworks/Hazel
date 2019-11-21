#include "hzpch.h"
#include "Events/ApplicationEvent.h"

#include <sstream>

namespace Hazel {

   WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height) {}


   uint32_t WindowResizeEvent::GetWidth() const {
      return m_width;
   }


   uint32_t  WindowResizeEvent::GetHeight() const {
      return m_height;
   }


   std::string WindowResizeEvent::ToString() const {
      std::stringstream ss;
      ss << "WindowResizeEvent: " << m_width << ", " << m_height;
      return ss.str();
   }


   WindowCloseEvent::WindowCloseEvent() {}


   AppTickEvent::AppTickEvent() {}


   AppUpdateEvent::AppUpdateEvent() {}


   AppRenderEvent::AppRenderEvent() {}

}