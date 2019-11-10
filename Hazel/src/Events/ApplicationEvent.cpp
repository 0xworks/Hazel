#include "hzpch.h"
#include "Events/ApplicationEvent.h"

#include <sstream>

namespace Hazel {

   WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}


   uint32_t WindowResizeEvent::GetWidth() const {
      return m_Width;
   }


   uint32_t  WindowResizeEvent::GetHeight() const {
      return m_Height;
   }


   std::string WindowResizeEvent::ToString() const {
      std::stringstream ss;
      ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
      return ss.str();
   }


   WindowCloseEvent::WindowCloseEvent() {}


   AppTickEvent::AppTickEvent() {}


   AppUpdateEvent::AppUpdateEvent() {}


   AppRenderEvent::AppRenderEvent() {}

}