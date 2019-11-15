#include "pch.h"
#include "glm/ext.hpp"

class ExampleLayer : public Hazel::Layer {
public:
   ExampleLayer() {
      m_vertexArray = Hazel::VertexArray::Create();

      float vertices[3 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
          0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
      };

      std::unique_ptr<Hazel::VertexBuffer> vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
      Hazel::BufferLayout layout = {
         {"a_Position", Hazel::ShaderDataType::Float3},
         {"a_Color",    Hazel::ShaderDataType::Float4}
      };
      vertexBuffer->SetLayout(layout);

      m_vertexArray->AddVertexBuffer(std::move(vertexBuffer));

      uint32_t indices[3] = {0, 1, 2};
      std::unique_ptr<Hazel::IndexBuffer> indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

      m_vertexArray->SetIndexBuffer(std::move(indexBuffer));

      m_squareVA = Hazel::VertexArray::Create();
      float verticesSquare[3 * 4] = {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.5f,  0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f,
      };
      std::unique_ptr<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare) / sizeof(float));

      squareVB->SetLayout({
         {"a_Position", Hazel::ShaderDataType::Float3}
      });

      m_squareVA->AddVertexBuffer(std::move(squareVB));

      uint32_t indicesSquare[6] = {0, 1, 2, 2, 3, 0};
      std::unique_ptr<Hazel::IndexBuffer> squareIB = Hazel::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));

      m_squareVA->SetIndexBuffer(std::move(squareIB));

      std::string vertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;
         layout(location = 1) in vec4 a_color;

         uniform mat4 u_viewProjection;
         uniform mat4 u_transform;

         out vec3 v_position;
         out vec4 v_color;

         void main() {
            v_position = a_position;
            v_color = a_color;
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
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

      m_shader = std::make_unique<Hazel::Shader>(vertexSrc, fragmentSrc);

      std::string vertexBlueSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;

         uniform mat4 u_viewProjection;
         uniform mat4 u_transform;

         out vec3 v_position;

         void main() {
            v_position = a_position;
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
         }
      )";

      std::string fragmentBlueSrc = R"(
         #version 330 core

         out vec4 color;

         void main() {
            color = vec4(0.2, 0.3, 0.8, 1.0);
         }
      )";

      m_shaderBlue = std::make_unique<Hazel::Shader>(vertexBlueSrc, fragmentBlueSrc);
   }


   virtual void OnUpdate(Hazel::Timestep ts) override {

      //HZ_CORE_INFO("Delta time = {0}ms", deltaTime.GetMilliseconds());

      float deltaTime = ts;
      if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT)) {
         m_cameraPosition.x -= (m_cameraMoveSpeed * deltaTime);
      } else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT)) {
         m_cameraPosition.x += (m_cameraMoveSpeed * deltaTime);
      }

      if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN)) {
         m_cameraPosition.y -= (m_cameraMoveSpeed * deltaTime);
      } else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP)) {
         m_cameraPosition.y += (m_cameraMoveSpeed * deltaTime);
      }

      if (Hazel::Input::IsKeyPressed(HZ_KEY_A)) {
         m_cameraRotation += (m_cameraRotationSpeed * deltaTime);
      } else if (Hazel::Input::IsKeyPressed(HZ_KEY_D)) {
         m_cameraRotation -= (m_cameraRotationSpeed * deltaTime);
      }

      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      Hazel::RenderCommand::Clear();

      m_camera.SetPosition(m_cameraPosition);
      m_camera.SetRotation(m_cameraRotation);

      glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.1f));

      Hazel::Renderer::BeginScene(m_camera);

      for (int y = -10; y < 10; ++y) {
         for (int x = -10; x < 10; ++x) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), pos) * scale;
            Hazel::Renderer::Submit(*m_shaderBlue, *m_squareVA, transform);
         }
      }
      Hazel::Renderer::Submit(*m_shader, *m_vertexArray, glm::identity<glm::mat4>());
      Hazel::Renderer::EndScene();
   }

private:
   Hazel::OrthographicCamera m_camera = {-1.6f, 0.9f, 1.6f, -0.9f};
   glm::vec3 m_cameraPosition = glm::zero<glm::vec3>();
   float m_cameraRotation = 0.0f;
   float m_cameraMoveSpeed = 5.0f;
   float m_cameraRotationSpeed = 180.0f;
   std::unique_ptr<Hazel::VertexArray> m_vertexArray;
   std::unique_ptr<Hazel::Shader> m_shader;
   std::unique_ptr<Hazel::VertexArray> m_squareVA;
   std::unique_ptr<Hazel::Shader> m_shaderBlue;
};

class Sandbox : public Hazel::Application {
public:
   Sandbox() {
      PushLayer(std::move(std::make_unique<ExampleLayer>()));
   }

   ~Sandbox() {}
};


std::unique_ptr<Hazel::Application> CreateApplication() {
   return std::make_unique<Sandbox>();
}
