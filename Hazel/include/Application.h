#pragma once

#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

#include <memory>

namespace Hazel {

   class Application {

   public:
      Application();
      virtual ~Application();

      void Run();

      void OnEvent(Event& e);

      void PushLayer(std::unique_ptr<Layer> layer);

      void PushOverlay(std::unique_ptr<Layer> overlay);

      Window& GetWindow();

      static Application& Get();

   private:
      bool OnWindowClose(WindowCloseEvent& event);

   private:
      LayerStack m_layerStack;
      float m_lastFrameTime = 0.0f;
      std::unique_ptr<Window> m_window;
      bool m_bRunning = true;

   private:
      static Application* sm_application;

   };

}


// Must be defined in client
extern std::unique_ptr<Hazel::Application> CreateApplication();
