#include "hzpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "glad/glad.h"
#include "Input.h"
#include "Log.h"

namespace Hazel {

   Application* Application::sm_application = nullptr;


   GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
      switch (type) {
         case ShaderDataType::Float:   return GL_FLOAT;
         case ShaderDataType::Float2:  return GL_FLOAT;
         case ShaderDataType::Float3:  return GL_FLOAT;
         case ShaderDataType::Float4:  return GL_FLOAT;
         case ShaderDataType::Mat3:    return GL_FLOAT;
         case ShaderDataType::Mat4:    return GL_FLOAT;
         case ShaderDataType::Int:     return GL_INT;
         case ShaderDataType::Int2:    return GL_INT;
         case ShaderDataType::Int3:    return GL_INT;
         case ShaderDataType::Int4:    return GL_INT;
         case ShaderDataType::Bool:    return GL_BOOL;
      }
      HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
      return 0;
   }


   Application::Application() {
      HZ_CORE_ASSERT(!sm_application, "Application already exists!");
      sm_application = this;
      m_window = std::unique_ptr<Window>(Window::Create());
      m_window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
      PushOverlay(std::make_unique<ImGuiLayer>());

      glGenVertexArrays(1, &m_vertexArray);
      glBindVertexArray(m_vertexArray);

      float vertices[3 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
          0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
      };

      m_vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

      BufferLayout layout = {
         {"a_Position", ShaderDataType::Float3},
         {"a_Color",    ShaderDataType::Float4}
      };
      m_vertexBuffer->SetLayout(layout);

      uint32_t index = 0;
      for (const auto& element : layout) {
         glEnableVertexAttribArray(index);
         glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)element.Offset
         );
         ++index;
      }

      uint32_t indices[3] = {0, 1, 2};
      m_indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

      std::string vertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;
         layout(location = 1) in vec4 a_color;

         out vec3 v_position;
         out vec4 v_color;

         void main() {
            v_position = a_position;
            v_color = a_color;
            gl_Position = vec4(a_position, 1.0);
         }
      )";

      std::string fragmentSrc = R"(
         #version 330 core

         layout(location = 0) out vec4 color;
         in vec3 v_position;
         in vec4 v_color;

         void main() {
            color = vec4(v_color);
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
         for(auto& layer : m_layerStack) {
            layer->OnUpdate();
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


   void Application::PushLayer(std::unique_ptr<Layer> layer) {
      m_layerStack.PushLayer(std::move(layer));
   }


   void Application::PushOverlay(std::unique_ptr<Layer> overlay) {
      m_layerStack.PushOverlay(std::move(overlay));
   }


   Window& Application::GetWindow() {
      HZ_CORE_ASSERT(m_window, "Window is null!");
      return(*m_window);
   }


   Application& Application::Get() {
      HZ_CORE_ASSERT(sm_application, "Application is null!");
      return(*sm_application);
   }


   bool Application::OnWindowClose(WindowCloseEvent& event) {
      m_bRunning = false;
      return(true);
   }

}