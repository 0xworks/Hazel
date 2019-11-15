#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "ImGuiLayer.h"
#include "LayerStack.h"
#include "Core/Timestep.h"
#include "Renderer/Shader.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Window.h"

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
