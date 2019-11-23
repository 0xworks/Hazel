#pragma once

#include "Platform/OpenGL/OpenGLShader.h"

class Sandbox2DLayer : public Hazel::Layer {
public:
   Sandbox2DLayer()
   : Hazel::Layer("Sandbox2D")
   , m_cameraController(/*aspectRatio=*/1280.0f / 720.0f, /*allowRotation=*/true)
   , m_squareColor(0.2f, 0.3f, 0.8f, 1.0f)
   {}


   virtual void OnAttach() override {

      m_squareVA = Hazel::VertexArray::Create();
      float verticesSquare[3 * 4] = {
         -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f
      };
      std::unique_ptr<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(verticesSquare, sizeof(verticesSquare) / sizeof(float));

      squareVB->SetLayout({
         {"a_Position", Hazel::ShaderDataType::Float3}
      });

      m_squareVA->AddVertexBuffer(std::move(squareVB));

      uint32_t indicesSquare[6] = {0, 1, 2, 2, 3, 0};
      std::unique_ptr<Hazel::IndexBuffer> squareIB = Hazel::IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t));

      m_squareVA->SetIndexBuffer(std::move(squareIB));

      m_flatColorShader = Hazel::Shader::Create("Assets/Shaders/FlatColor.glsl");

   }


   virtual void OnDetach() override {
   }


   virtual void OnUpdate(Hazel::Timestep deltaTime) override {
      // Update
      m_cameraController.OnUpdate(deltaTime);

      // Render
      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      Hazel::RenderCommand::Clear();

      Hazel::Renderer::BeginScene(m_cameraController.GetCamera());

      m_flatColorShader->Bind();
      ((Hazel::OpenGLShader*)m_flatColorShader.get())->UploadUniformVec4("u_color", m_squareColor);

      Hazel::Renderer::Submit(*m_flatColorShader, *m_squareVA, glm::scale(glm::identity<glm::mat4>(), glm::vec3(1.5f)));

      Hazel::Renderer::EndScene();
   }


   virtual void OnEvent(Hazel::Event& e) override {
      m_cameraController.OnEvent(e);
   }


   virtual void OnImGuiRender() override {
      ImGui::Begin("Settings");
      ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
      ImGui::End();
   }

private:
   Hazel::OrthographicCameraController m_cameraController;

   // temporary
   glm::vec4 m_squareColor;
   std::unique_ptr<Hazel::Shader> m_flatColorShader;
   std::unique_ptr<Hazel::VertexArray> m_squareVA;


};
