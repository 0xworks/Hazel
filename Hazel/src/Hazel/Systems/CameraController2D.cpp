#include "hzpch.h"
#include "Hazel/Systems/CameraController2D.h"

#include "Hazel/Components/Camera.h"
#include "Hazel/Components/CameraSettings.h"
#include "Hazel/Components/Transform.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/ECS/ECS.h"
#include "Hazel/Events/Events.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"

#include <glm/gtc/matrix_transform.hpp>

#define M_PI_FLOAT 3.14159265358979323846f

namespace Hazel {

   void CameraController2D::Init(float translationSpeed, float rotationSpeed, bool isRotationEnabled) {
      m_translationSpeed = translationSpeed;
      m_rotationSpeed = rotationSpeed;
      m_isRotationEnabled = isRotationEnabled;
      Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Mouse::SCROLLED, CameraController2D::OnMouseScrolled));
      Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Window::RESIZE, CameraController2D::OnWindowResized)); // should probably be in Render system
   }


   void CameraController2D::Update(Timestep deltaTime) {
      for (auto entity : m_entities) {
         if (Input::IsKeyPressed(HZ_KEY_A)) {
            auto& transform = ECS::GetComponent<Transform>(entity);
            transform.Position.x -= cos(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            transform.Position.y -= sin(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            RecalculateViewMatrix(entity);
         } else if (Input::IsKeyPressed(HZ_KEY_D)) {
            auto& transform = ECS::GetComponent<Transform>(entity);
            transform.Position.x += cos(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            transform.Position.y += sin(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            RecalculateViewMatrix(entity);
         }

         if (Input::IsKeyPressed(HZ_KEY_W)) {
            auto& transform = ECS::GetComponent<Transform>(entity);
            transform.Position.x += -sin(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            transform.Position.y += cos(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            RecalculateViewMatrix(entity);
         } else if (Input::IsKeyPressed(HZ_KEY_S)) {
            auto& transform = ECS::GetComponent<Transform>(entity);
            transform.Position.x -= -sin(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            transform.Position.y -= cos(transform.RotationRadians.z) * m_translationSpeed * deltaTime;
            RecalculateViewMatrix(entity);
         }

         if (m_isRotationEnabled) {
            if (Input::IsKeyPressed(HZ_KEY_Q)) {
               auto& transform = ECS::GetComponent<Transform>(entity);
               transform.RotationRadians.z += (m_rotationSpeed * deltaTime);
               if (transform.RotationRadians.z > M_PI_FLOAT) {
                  transform.RotationRadians.z -= 2.0f * static_cast<float>(M_PI_FLOAT);
               }
               RecalculateViewMatrix(entity);
            } else if (Input::IsKeyPressed(HZ_KEY_E)) {
               auto& transform = ECS::GetComponent<Transform>(entity);
               transform.RotationRadians.z -= (m_rotationSpeed * deltaTime);
               if (transform.RotationRadians.z <= -M_PI_FLOAT) {
                  transform.RotationRadians.z += 2 * M_PI_FLOAT;
               }
               RecalculateViewMatrix(entity);
            }
         }
      }
   }


   void CameraController2D::OnMouseScrolled(Event& event) {
      auto yOffset = event.GetParam<float>(Events::Mouse::Scrolled::YOFFSET);

      for (auto entity : m_entities) {
         auto& cameraSettings = ECS::GetComponent<CameraSettings>(entity);
         auto& camera = ECS::GetComponent<Camera>(entity);

         cameraSettings.Zoom -= yOffset * 0.5f;
         cameraSettings.Zoom = std::max(cameraSettings.Zoom, 0.25f);

         m_translationSpeed = cameraSettings.Zoom;

         camera.ProjectionMatrix = Camera::MakeOrthographic(-cameraSettings.AspectRatio * cameraSettings.Zoom, cameraSettings.Zoom, cameraSettings.AspectRatio * cameraSettings.Zoom, -cameraSettings.Zoom);
         camera.ViewProjectionMatrix = camera.ProjectionMatrix * camera.ViewMatrix;
      }
   }


   void CameraController2D::OnWindowResized(Event& event) {
      auto windowWidth = event.GetParam<int>(Events::Window::Resize::WIDTH);
      auto windowHeight = event.GetParam<int>(Events::Window::Resize::HEIGHT);

      for (auto entity : m_entities) {
         auto& cameraSettings = ECS::GetComponent<CameraSettings>(entity);
         auto& camera = ECS::GetComponent<Camera>(entity);

         cameraSettings.AspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);

         camera.ProjectionMatrix = Camera::MakeOrthographic(-cameraSettings.AspectRatio * cameraSettings.Zoom, cameraSettings.Zoom, cameraSettings.AspectRatio * cameraSettings.Zoom, -cameraSettings.Zoom);
         camera.ViewProjectionMatrix = camera.ProjectionMatrix * camera.ViewMatrix;
      }
   }


   void 	CameraController2D::RecalculateViewMatrix(ECS::Entity entity) {
      HZ_PROFILE_FUNCTION();

      auto& camera = ECS::GetComponent<Camera>(entity);
      auto& transform = ECS::GetComponent<Transform>(entity);

      glm::mat4 viewMatrix = glm::translate(glm::identity<glm::mat4>(), transform.Position) * glm::rotate(glm::identity<glm::mat4>(), transform.RotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f));

      camera.ViewMatrix = glm::inverse(viewMatrix);
      camera.ViewProjectionMatrix = camera.ProjectionMatrix * camera.ViewMatrix;
   }

}