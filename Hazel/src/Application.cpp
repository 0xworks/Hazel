#include "hzpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "glad/glad.h"
#include "Input.h"
#include "Log.h"

namespace Hazel {

   Application* Application::m_spApp = nullptr;


   Application::Application() {
      HZ_CORE_ASSERT(!m_spApp, "Application already exists!");
      m_spApp = this;
      m_pWindow = std::unique_ptr<Window>(Window::Create());
      m_pWindow->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
      m_pImGuiLayer = new ImGuiLayer;
      PushOverlay(m_pImGuiLayer);
   }


   Application::~Application() {}


   void Application::Run() {

      while(m_bRunning) {

         // does not belong here.
         // Application should not have to know that it's OpenGL under the hood.
         // Doesnt really belong in WindowsWindow either.. as that class is for Windows specific implementation
         glClearColor(1, 0, 1, 1);
         glClear(GL_COLOR_BUFFER_BIT);

         auto [x, y] = Input::GetMousePosition();
         HZ_CORE_TRACE("mouse = {0}, {1}", x, y);

         for(Layer* pLayer : m_layerStack) {
            pLayer->OnUpdate();
         }

         m_pImGuiLayer->Begin();
         for(Layer* pLayer : m_layerStack) {
            pLayer->OnImGuiRender();
         }
         m_pImGuiLayer->End();

         m_pWindow->OnUpdate();
      }
   }


   void Application::OnEvent(Event& e) {
      HZ_CORE_TRACE("{0}", e);

      // JRW: I am not convinced about this.
      // This seems like an overly complicated way to just do a switch on event type...
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

      //switch(e.GetEventType()) {
      //   case EventType::WindowClose:
      //      OnWindowClose((WindowCloseEvent&)e);
      //      break;
      //}

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