#include "include/hzpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel {

   Application::Application() {
      m_pWindow = std::unique_ptr<Window>(Window::Create());
      m_pWindow->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
   }


   Application::~Application() {}


   void Application::Run() {

      while(m_bRunning) {
         m_pWindow->OnUpdate();
      }
   }


   void Application::OnEvent(Event& e) {
      HZ_CORE_TRACE("{0}", e);
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
   }


   bool Application::OnWindowClose(WindowCloseEvent& event) {
      m_bRunning = false;
      return(true);
   }

}