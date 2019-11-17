#include "pch.h"
#include "glm/ext.hpp"
#include "vendor/imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

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
      float verticesSquare[5 * 4] = {
         -0.5f, -0.5f, 0.0f, 0.0, 0.0,
          0.5f, -0.5f, 0.0f, 1.0, 0.0,
          0.5f,  0.5f, 0.0f, 1.0, 1.0,
         -0.5f,  0.5f, 0.0f, 0.0, 1.0,
      };
      std::unique_ptr<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare) / sizeof(float));

      squareVB->SetLayout({
         {"a_Position", Hazel::ShaderDataType::Float3},
         {"a_TexCoord", Hazel::ShaderDataType::Float2}
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

         out vec4 v_color;

         void main() {
            v_color = a_color;
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
         }
      )";

      std::string fragmentSrc = R"(
         #version 330 core

         layout(location = 0) out vec4 color;

         in vec4 v_color;

         void main() {
            color = vec4(v_color);
         }
      )";

      m_shader = Hazel::Shader::Create(vertexSrc, fragmentSrc);

      std::string flatColorVertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;

         uniform mat4 u_viewProjection;
         uniform mat4 u_transform;

         void main() {
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
         }
      )";

      std::string flatColorFragmentSrc = R"(
         #version 330 core

         layout(location = 0) out vec4 color;

         uniform vec3 u_color;

         void main() {
            color = vec4(u_color, 1.0);
         }
      )";

      m_flatColorShader = Hazel::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc);

      std::string textureVertexSrc = R"(
         #version 330 core

         layout(location = 0) in vec3 a_position;
         layout(location = 1) in vec2 a_texCoord;

         uniform mat4 u_viewProjection;
         uniform mat4 u_transform;

         out vec2 v_texCoord;

         void main() {
            v_texCoord = a_texCoord;
            gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
         }
      )";

      std::string textureFragmentSrc = R"(
         #version 330 core

         layout(location = 0) out vec4 color;

         in vec2 v_texCoord;

         uniform sampler2D u_texture;

         void main() {
            color = texture(u_texture, v_texCoord);
         }
      )";

      m_textureShader = Hazel::Shader::Create(textureVertexSrc, textureFragmentSrc);
      m_texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
      m_chernoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

      m_textureShader->Bind();
      ((Hazel::OpenGLShader*)m_textureShader.get())->UploadUniformUInt("u_Texture", 0); // TODO: parameterise texture slot?

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

      if (Hazel::Input::IsKeyPressed(HZ_KEY_Q)) {
         m_cameraRotation += (m_cameraRotationSpeed * deltaTime);
      } else if (Hazel::Input::IsKeyPressed(HZ_KEY_E)) {
         m_cameraRotation -= (m_cameraRotationSpeed * deltaTime);
      }

      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      Hazel::RenderCommand::Clear();

      m_camera.SetPosition(m_cameraPosition);
      m_camera.SetRotation(m_cameraRotation);

      glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.1f));

      Hazel::Renderer::BeginScene(m_camera);

      m_flatColorShader->Bind();
      ((Hazel::OpenGLShader*)m_flatColorShader.get())->UploadUniformVec3("u_color", m_squareColor);

      // Grid squares
      for (int y = -10; y < 10; ++y) {
         for (int x = -10; x < 10; ++x) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), pos) * scale;
            Hazel::Renderer::Submit(*m_flatColorShader, *m_squareVA, transform);
         }
      }

     // Big squares
      m_texture->Bind(0);
      Hazel::Renderer::Submit(*m_textureShader, *m_squareVA, glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.5f)));

      m_chernoTexture->Bind(0);
      Hazel::Renderer::Submit(*m_textureShader, *m_squareVA, glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.5f)));

      // Triangle
      //Hazel::Renderer::Submit(*m_shader, *m_vertexArray, glm::identity<glm::mat4>());

      Hazel::Renderer::EndScene();
   }

   virtual void OnImGuiRender() override {
      ImGui::Begin("Settings");
      ImGui::ColorEdit3("Square Color", glm::value_ptr(m_squareColor));
      ImGui::End();
   }
private:
   Hazel::OrthographicCamera m_camera = {-3.2f, 1.8f, 3.2f, -1.8f};
   glm::vec3 m_cameraPosition = glm::zero<glm::vec3>();
   glm::vec3 m_squareColor = {0.2f, 0.3f, 0.8f};
   float m_cameraRotation = 0.0f;
   float m_cameraMoveSpeed = 5.0f;
   float m_cameraRotationSpeed = 180.0f;
   std::unique_ptr<Hazel::VertexArray> m_vertexArray;
   std::unique_ptr<Hazel::Shader> m_shader;
   std::unique_ptr<Hazel::VertexArray> m_squareVA;
   std::unique_ptr<Hazel::Shader> m_flatColorShader;
   std::unique_ptr<Hazel::Shader> m_textureShader;
   std::unique_ptr<Hazel::Texture2D> m_texture;
   std::unique_ptr<Hazel::Texture2D> m_chernoTexture;
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
