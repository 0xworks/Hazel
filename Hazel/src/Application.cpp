#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel {

   Application::Application() {
      m_pWindow = std::unique_ptr<Window>(Window::Create());
   }


   Application::~Application() {}

   void Application::Run() {

      while(m_bRunning) {
         m_pWindow->OnUpdate();
      }
   }

}