#pragma once

#include "Core.h"
#include "ImGuiLayer.h"
#include "LayerStack.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

namespace Hazel {

   class Application {
   public:
      Application();
      virtual ~Application();

      void Run();

      void OnEvent(Event& e);

      void PushLayer(Layer* pLayer);

      void PushOverlay(Layer* pLayerOverlay);

      Window& GetWindow();

      static Application& Get();

   private:

      static Application* m_spApp;

      bool OnWindowClose(WindowCloseEvent& event);

      LayerStack m_layerStack;
      std::unique_ptr<Window> m_pWindow;
      ImGuiLayer* m_pImGuiLayer;
      bool m_bRunning = true;
   };

}


// Must be defined in client
extern Hazel::Application* CreateApplication();
