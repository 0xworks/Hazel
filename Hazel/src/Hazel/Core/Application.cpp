#include "hzpch.h"
#include "Hazel/Core/Application.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/ImGuiLayer.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Events/Events.h"
#include "Hazel/Events/WindowEvent.h"
#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Hazel {

   Application* Application::sm_application = nullptr;


   Application::Application() {
      HZ_CORE_ASSERT(!sm_application, "Application already exists!");
      sm_application = this;
      m_window = Window::Create();

      Renderer::Init();

      Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Window::RESIZE, Application::OnWindowResize));
      Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Window::CLOSE, Application::OnWindowClose));

      PushOverlay(std::make_unique<ImGuiLayer>());
   }


   Application::~Application() {
      Renderer::ShutDown();
   }


   void Application::Run() {
      HZ_PROFILE_FUNCTION();

      while(m_isRunning) {
         float time = (float)glfwGetTime(); // this should be in Platform/...
         Timestep deltaTime = (time - m_lastFrameTime);
         m_lastFrameTime = time;

         if (!m_isMinimised) {
            for (auto& layer : m_layerStack) {
               layer->OnUpdate(deltaTime);
            }
         }

         HZ_PROFILE_SCOPE("ImGuiLayer");
         ImGuiLayer::Begin();
         for(auto& layer : m_layerStack) {
            layer->OnImGuiRender();
         }
         ImGuiLayer::End();

         m_window->OnUpdate();
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


   void Application::OnWindowClose(Event&) {
      m_isRunning = false;
   }


   void Application::OnWindowResize(Event& event) {
      int width = event.GetParam<int>(Events::Window::Resize::WIDTH);
      int height = event.GetParam<int>(Events::Window::Resize::HEIGHT);
      if (width == 0 || height == 0) {
         m_isMinimised = true;
      } else {
         m_isMinimised = false;
         Renderer::OnWindowResized(width, height);
      }
   }

}