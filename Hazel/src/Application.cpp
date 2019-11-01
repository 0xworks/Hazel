#include "hzpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel {

   Application* Application::m_spApp = nullptr;


   Application::Application() {
      HZ_CORE_ASSERT(!m_spApp, "Application already exists!");
      m_spApp = this;
      m_pWindow = std::unique_ptr<Window>(Window::Create());
      m_pWindow->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
   }


   Application::~Application() {}


   void Application::Run() {

      while(m_bRunning) {
         for(Layer* pLayer : m_layerStack) {
            pLayer->OnUpdate();
         }
         m_pWindow->OnUpdate();
      }
   }


   void Application::OnEvent(Event& e) {
      HZ_CORE_TRACE("{0}", e);

      // JRW: I am not convinced about this.
      // This seems like an overly complicated way to just do a switch on event type...
      //EventDispatcher dispatcher(e);
      //dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

      switch(e.GetEventType()) {
         case EventType::WindowClose:
            OnWindowClose((WindowCloseEvent&)e);
            break;
      }

      for(auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it) {
         (*it)->OnEvent(e);
         if(e.IsHandled()) {
            break;
         }
      }
   }


   void Application::PushLayer(Layer* pLayer) {
      m_layerStack.PushLayer(pLayer);
      pLayer->OnAttach();
   }


   void Application::PushOverlay(Layer* pLayerOverlay) {
      m_layerStack.PushOverlay(pLayerOverlay);
   }


   Window& Application::GetWindow() {
      HZ_CORE_ASSERT(m_pWindow, "Window is null!");
      return(*m_pWindow);
   }


   Application& Application::Get() {
      HZ_CORE_ASSERT(m_spApp, "Application is null!");
      return(*m_spApp);
   }


   bool Application::OnWindowClose(WindowCloseEvent& event) {
      m_bRunning = false;
      return(true);
   }

}