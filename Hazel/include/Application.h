#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "ImGuiLayer.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/IndexBuffer.h"
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

      static Application* sm_application;

      bool OnWindowClose(WindowCloseEvent& event);

      LayerStack m_layerStack;
      std::unique_ptr<Window> m_window;
      std::unique_ptr<Shader> m_shader;
      std::unique_ptr<VertexArray> m_vertexArray;
      std::shared_ptr<IndexBuffer> m_indexBuffer;
      std::shared_ptr<VertexBuffer> m_vertexBuffer;

      std::unique_ptr<VertexArray> m_squareVA;
      std::unique_ptr<Shader> m_shaderBlue;

      bool m_bRunning = true;
   };

}


// Must be defined in client
extern std::unique_ptr<Hazel::Application> CreateApplication();
