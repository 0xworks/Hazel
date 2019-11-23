#pragma once

#include "vendor/imgui/imgui.h"

// temporary
#include "glm/ext.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Hazel::Layer {
public:
   ExampleLayer()
   : Layer("Example")
   , m_cameraController(/*aspectRatio=*/1280.0f / 720.0f, /*allowRotation=*/true)
   , m_squareColor(0.2f, 0.3f, 0.8f, 1.0f)
   {
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

      m_shaderLibrary = std::make_unique<Hazel::ShaderLibrary>();
      m_shaderLibrary->LoadShader("Assets/Shaders/VertexColor.glsl");
      m_shaderLibrary->LoadShader("Assets/Shaders/FlatColor.glsl");
      m_shaderLibrary->LoadShader("Assets/Shaders/Texture.glsl");

      m_texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
      m_chernoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

      std::shared_ptr<Hazel::Shader> textureShader = m_shaderLibrary->GetShader("Texture");
      textureShader->Bind();
      ((Hazel::OpenGLShader*)textureShader.get())->UploadUniformUInt("u_Texture", 0); // TODO: parameterise texture slot?

   }


   virtual void OnEvent(Hazel::Event& e) override {
      m_cameraController.OnEvent(e);
   }


   virtual void OnUpdate(Hazel::Timestep ts) override {

      //HZ_CORE_INFO("Delta time = {0}ms", deltaTime.GetMilliseconds());

      // Update
      m_cameraController.OnUpdate(ts);

      // Render
      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      Hazel::RenderCommand::Clear();

      glm::mat4 scale = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.1f));

      Hazel::Renderer::BeginScene(m_cameraController.GetCamera());

      std::shared_ptr<Hazel::Shader> flatColorShader = m_shaderLibrary->GetShader("FlatColor");
      flatColorShader->Bind();
      ((Hazel::OpenGLShader*)flatColorShader.get())->UploadUniformVec4("u_color", m_squareColor);

      // Grid squares
      for (int y = -10; y < 10; ++y) {
         for (int x = -10; x < 10; ++x) {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), pos) * scale;
            Hazel::Renderer::Submit(*flatColorShader, *m_squareVA, transform);
         }
      }

      // Big squares
      std::shared_ptr<Hazel::Shader> textureShader = m_shaderLibrary->GetShader("Texture");
      m_texture->Bind(0);
      Hazel::Renderer::Submit(*textureShader, *m_squareVA, glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.5f)));

      m_chernoTexture->Bind(0);
      Hazel::Renderer::Submit(*textureShader, *m_squareVA, glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.5f)));

      // Triangle
      //Hazel::Renderer::Submit(*m_shader, *m_vertexArray, glm::identity<glm::mat4>());

      Hazel::Renderer::EndScene();
   }


   virtual void OnImGuiRender() override {
      ImGui::Begin("Settings");
      ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
      ImGui::End();
   }


private:
   Hazel::OrthographicCameraController m_cameraController;
   glm::vec4 m_squareColor;
   std::unique_ptr<Hazel::VertexArray> m_vertexArray;
   std::unique_ptr<Hazel::Shader> m_shader;
   std::unique_ptr<Hazel::VertexArray> m_squareVA;
   std::unique_ptr<Hazel::ShaderLibrary> m_shaderLibrary;
   std::unique_ptr<Hazel::Texture2D> m_texture;
   std::unique_ptr<Hazel::Texture2D> m_chernoTexture;
};
