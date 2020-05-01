#pragma once

#include "Hazel/Components/Camera.h"
#include "Hazel/Components/CameraSettings.h"
#include "Hazel/Components/Transform.h"
#include "Hazel/Systems/CameraController2D.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2DLayer : public Hazel::Layer {
public:
   Sandbox2DLayer()
   : Hazel::Layer("Sandbox2D")
   , m_camera(Hazel::ECS::CreateEntity())
   , m_squareColor(0.2f, 0.3f, 0.8f, 1.0f)
   {}


   virtual void OnAttach() override {
      m_texture = Hazel::Texture2D::Create("Assets/Textures/Checkerboard.png");

      Hazel::Transform transform {};
      Hazel::CameraSettings cameraSettings {};

      glm::mat4 projectionMatrix = glm::ortho(-cameraSettings.AspectRatio * cameraSettings.Zoom, cameraSettings.AspectRatio * cameraSettings.Zoom, -cameraSettings.Zoom, cameraSettings.Zoom, -1.0f, 1.0f); 

      Hazel::Camera camera {projectionMatrix, glm::identity<glm::mat4>(), projectionMatrix};

      // All systems must be registered and Init()ialised before you go adding any components to entities

      m_cameraController = Hazel::ECS::RegisterSystem<Hazel::CameraController2D>();
      {
         Hazel::ECS::Signature signature;
         signature.set(Hazel::ECS::GetComponentType<Hazel::Camera>());
         signature.set(Hazel::ECS::GetComponentType<Hazel::CameraSettings>());
         signature.set(Hazel::ECS::GetComponentType<Hazel::Transform>());
         Hazel::ECS::SetSystemSignature<Hazel::CameraController2D>(signature);
      }
      m_cameraController->Init(cameraSettings.Zoom, glm::radians(10.0f), true);

      Hazel::ECS::AddComponent(m_camera, transform);
      Hazel::ECS::AddComponent(m_camera, cameraSettings);
      Hazel::ECS::AddComponent(m_camera, camera);
   }


   virtual void OnDetach() override {
      m_texture = nullptr;
   }


   virtual void OnUpdate(Hazel::Timestep deltaTime) override {
      HZ_PROFILE_FUNCTION();
      // Update
      static float rotationDegrees = 0.0f;
      rotationDegrees += deltaTime * 50.0f;
      m_cameraController->Update(deltaTime);

      // Render
      Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
      Hazel::RenderCommand::Clear();

      Hazel::Renderer2D::BeginScene(m_camera);
      Hazel::Renderer2D::DrawQuad({-0.5f, 0.5f}, {1.0f,  1.0f}, glm::radians(45.0f), m_squareColor);
      Hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.75f, 0.5f}, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f});
      Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, -0.1f}, {10.0f, 10.0f}, 0.0f, *m_texture);
      Hazel::Renderer2D::DrawQuad({0.0f,  0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotationDegrees), *m_texture, 10.0f);
      Hazel::Renderer2D::EndScene();
   }


   virtual void OnImGuiRender() override {
      ImGui::Begin("Settings");
      ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
      ImGui::End();
   }

private:
   std::shared_ptr<Hazel::CameraController2D> m_cameraController;
   std::unique_ptr<Hazel::Texture> m_texture;
   Hazel::ECS::Entity m_camera;
   glm::vec4 m_squareColor;

};
