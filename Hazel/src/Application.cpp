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
      m_window = std::unique_ptr<Window>(Window::Create());
      m_window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
      m_imGuiLayer = new ImGuiLayer;
      PushOverlay(m_imGuiLayer);

      glGenVertexArrays(1, &m_vertexArray);
      glBindVertexArray(m_vertexArray);

      float vertices[3 * 3] = {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f, 
          0.0f,  0.5f, 0.0f
      };

      m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));
      m_vertexBuffer->Bind();

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), nullptr);

      unsigned int indices[3] = {0, 1, 2};
      m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

      std::string vertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;
         out vec3 v_position;

         void main() {
            v_position = a_position;
            gl_Position = vec4(a_position, 1.0);

         }
      )";

      std::string fragmentSrc = R"(
         #version 330 core

         layout(location = 0) out vec4 color;
         in vec3 v_position;

         void main() {
            color = vec4(v_position * 0.5 + 0.5, 1.0);
         }
      )";

      m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);

   }


   Application::~Application() {}


   void Application::Run() {

      while(m_bRunning) {

         // does not belong here.
         // Application should not have to know that it's OpenGL under the hood.
         // Doesnt really belong in WindowsWindow either.. as that class is for Windows specific implementation
         glClearColor(0.1f, 0.1f, 0.1f, 1);
         glClear(GL_COLOR_BUFFER_BIT);

         glBindVertexArray(m_vertexArray);
         m_shader->Bind();
         glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
         for(Layer* pLayer : m_layerStack) {
            pLayer->OnUpdate();
         }

         m_imGuiLayer->Begin();
         for(Layer* pLayer : m_layerStack) {
            pLayer->OnImGuiRender();
         }
         m_imGuiLayer->End();

         m_window->OnUpdate();
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
      HZ_CORE_ASSERT(m_window, "Window is null!");
      return(*m_window);
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