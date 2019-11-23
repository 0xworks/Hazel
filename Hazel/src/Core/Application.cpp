#include "hzpch.h"
#include "Core/Application.h"

#include "Core/Input.h"
#include "Core/ImGuiLayer.h"
#include "Core/Log.h"
#include "Events/ApplicationEvent.h"
#include "Renderer/Renderer.h"

#include "GLFW/glfw3.h"

namespace Hazel {

   Application* Application::sm_application = nullptr;


   Application::Application() {
      HZ_CORE_ASSERT(!sm_application, "Application already exists!");
      sm_application = this;
      m_window = Window::Create();
      m_window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

      Renderer::Init();

      PushOverlay(std::make_unique<ImGuiLayer>());
   }


   void Application::Run() {

      while(m_bRunning) {
         float time = (float)glfwGetTime(); // this should be in Platform/...
         Timestep deltaTime = (time - m_lastFrameTime);
         m_lastFrameTime = time;

         if (!m_bMinimised) {
            for (auto& layer : m_layerStack) {
               layer->OnUpdate(deltaTime);
            }
         }

         ImGuiLayer::Begin();
         for(auto& layer : m_layerStack) {
            layer->OnImGuiRender();
         }
         ImGuiLayer::End();

         m_window->OnUpdate();
      }
   }


   void Application::OnEvent(Event& e) {
      //HZ_CORE_TRACE("{0}", e);

      // JRW: I am not convinced about this.
      // This seems like an overly complicated way to just do a switch on event type...
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
      dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

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


   void Application::PushLayer(std::unique_ptr<Layer> layer) {
      m_layerStack.PushLayer(std::move(layer));
   }


   void Application::PushOverlay(std::unique_ptr<Layer> overlay) {
      m_layerStack.PushOverlay(std::move(overlay));
   }


   Window& Application::GetWindow() {
      HZ_CORE_ASSERT(m_window, "Window is null!");
      return *m_window;
   }


   Application& Application::Get() {
      HZ_CORE_ASSERT(sm_application, "Application is null!");
      return *sm_application;
   }


   bool Application::OnWindowClose(WindowCloseEvent& e) {
      m_bRunning = false;
      return true;
   }

   bool Application::OnWindowResize(WindowResizeEvent& e) {
      if (e.GetWidth() == 0 || e.GetHeight() == 0) {
         m_bMinimised = true;
      } else {
         m_bMinimised = false;
         Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
      }
      return false;
   }

}