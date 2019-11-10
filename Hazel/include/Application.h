#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "ImGuiLayer.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Window.h"


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
      std::unique_ptr<Window> m_window;
      std::unique_ptr<Shader> m_shader;
      std::unique_ptr<IndexBuffer> m_indexBuffer;
      std::unique_ptr<VertexBuffer> m_vertexBuffer;
      ImGuiLayer* m_imGuiLayer;
      uint32_t m_vertexArray;

      bool m_bRunning = true;
   };

}


// Must be defined in client
extern Hazel::Application* CreateApplication();
