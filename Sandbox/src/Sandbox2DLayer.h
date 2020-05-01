#pragma once

class Sandbox2DLayer : public Hazel::Layer {
public:
   Sandbox2DLayer()
   : Hazel::Layer("Sandbox2D")
   , m_cameraController(/*aspectRatio=*/1280.0f / 720.0f, /*allowRotation=*/true)
   , m_squareColor(0.2f, 0.3f, 0.8f, 1.0f)
   {}


   virtual void OnAttach() override {
      m_texture = Hazel::Texture2D::Create("Assets/Textures/Checkerboard.png");
   }


   virtual void OnDetach() override {
      m_texture = nullptr;
   }


   virtual void OnUpdate(Hazel::Timestep deltaTime) override {
      HZ_PROFILE_FUNCTION();
      // Update
      static float rotationDegrees = 0.0f;
      rotationDegrees += deltaTime * 50.0f;
      m_cameraController.OnUpdate(deltaTime);

      // Render
      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
      Hazel::RenderCommand::Clear();

      Hazel::Renderer2D::BeginScene(m_cameraController.GetCamera());
      Hazel::Renderer2D::DrawQuad({-0.5f, 0.5f}, {1.0f,  1.0f}, glm::radians(45.0f), m_squareColor);
      Hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.75f, 0.5f}, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f});
      Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, -0.1f}, {10.0f, 10.0f}, 0.0f, *m_texture);
      Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotationDegrees), *m_texture, 10.0f);
      Hazel::Renderer2D::EndScene();
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
   std::unique_ptr<Hazel::Texture> m_texture;
   glm::vec4 m_squareColor;

};
