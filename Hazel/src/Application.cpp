#include "hzpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Input.h"
#include "Log.h"
#include "Renderer/Renderer.h"

namespace Hazel {

   Application* Application::sm_application = nullptr;


   Application::Application()
   : m_camera(-1.6, 0.9f, 1.6f, -0.9f)
   {
      HZ_CORE_ASSERT(!sm_application, "Application already exists!");
      sm_application = this;
      m_window = std::unique_ptr<Window>(Window::Create());
      m_window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));
      PushOverlay(std::make_unique<ImGuiLayer>());

      m_vertexArray = VertexArray::Create();

      float vertices[3 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
          0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
      };

      std::unique_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
      BufferLayout layout = {
         {"a_Position", ShaderDataType::Float3},
         {"a_Color",    ShaderDataType::Float4}
      };
      vertexBuffer->SetLayout(layout);

      m_vertexArray->AddVertexBuffer(std::move(vertexBuffer));

      uint32_t indices[3] = {0, 1, 2};
      std::unique_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

      m_vertexArray->SetIndexBuffer(std::move(indexBuffer));

      m_squareVA = VertexArray::Create();
      float verticesSquare[3 * 4] = {
         -0.75f, -0.75f, 0.0f,
          0.75f, -0.75f, 0.0f,
          0.75f,  0.75f, 0.0f,
         -0.75f,  0.75f, 0.0f,
      };
      std::unique_ptr<VertexBuffer> squareVB = VertexBuffer::Create(verticesSquare, sizeof(verticesSquare) / sizeof(float));

      squareVB->SetLayout({
         {"a_Position", ShaderDataType::Float3}
      });

      m_squareVA->AddVertexBuffer(std::move(squareVB));

      uint32_t indicesSquare[6] = {0, 1, 2, 2, 3, 0};
      std::unique_ptr<IndexBuffer> squareIB = IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));

      m_squareVA->SetIndexBuffer(std::move(squareIB));

      std::string vertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;
         layout(location = 1) in vec4 a_color;

         uniform mat4 u_ViewProjection;

         out vec3 v_position;
         out vec4 v_color;

         void main() {
            v_position = a_position;
            v_color = a_color;
            gl_Position = u_ViewProjection * vec4(a_position, 1.0);
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

      std::string vertexBlueSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;

         uniform mat4 u_ViewProjection;

         out vec3 v_position;

         void main() {
            v_position = a_position;
            gl_Position = u_ViewProjection * vec4(a_position, 1.0);
         }
      )";

      std::string fragmentBlueSrc = R"(
         #version 330 core

         out vec4 color;

         void main() {
            color = vec4(0.2, 0.3, 0.8, 1.0);
         }
      )";

      m_shaderBlue = std::make_unique<Shader>(vertexBlueSrc, fragmentBlueSrc);

   }


   Application::~Application() {}


   void Application::Run() {

      while(m_bRunning) {

         RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
         RenderCommand::Clear();

         m_camera.SetRotation(45.0f);
         m_camera.SetPosition({0.5f, 0.5f, 0.0f});

         Renderer::BeginScene(m_camera);
         Renderer::Submit(*m_shaderBlue, *m_squareVA);
         Renderer::Submit(*m_shader, *m_vertexArray);
         Renderer::EndScene();

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