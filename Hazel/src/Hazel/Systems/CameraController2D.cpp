#include "hzpch.h"
#include "Hazel/Systems/CameraController2D.h"

#include "Hazel/Components/Transform.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/ECS/ECS.h"
#include "Hazel/Events/Events.h"
#include "Hazel/Events/MouseEvent.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Hazel {

   void CameraController2D::Init() {
      Events::AddEventListener(HZ_BIND_EVENT_METHOD(Events::Mouse::SCROLLED, CameraController2D::OnMouseScrolled));
   }


   void CameraController2D::Update(Timestep deltaTime) {

      const float translationSpeed = 20.0f;  // TODO: find better place for these
      const float rotationSpeed = 10.0f;
      const bool isRotationEnabled = true;

      for (auto& entity : m_entities) {
         auto& transform = ECS::GetComponent<Transform>(entity);

         if (Input::IsKeyPressed(HZ_KEY_A)) {
            transform.Position.x -= cos(transform.RotationRadians.z) * translationSpeed * deltaTime;
            transform.Position.y -= sin(transform.RotationRadians.z) * translationSpeed * deltaTime;
         } else if (Input::IsKeyPressed(HZ_KEY_D)) {
            transform.Position.x += cos(transform.RotationRadians.z) * translationSpeed * deltaTime;
            transform.Position.y += sin(transform.RotationRadians.z) * translationSpeed * deltaTime;
         }

         if (Input::IsKeyPressed(HZ_KEY_W)) {
            transform.Position.x += -sin(transform.RotationRadians.z) * translationSpeed * deltaTime;
            transform.Position.y += cos(transform.RotationRadians.z) * translationSpeed * deltaTime;
         } else if (Input::IsKeyPressed(HZ_KEY_S)) {
            transform.Position.x -= -sin(transform.RotationRadians.z) * translationSpeed * deltaTime;
            transform.Position.y -= cos(transform.RotationRadians.z) * translationSpeed * deltaTime;
         }

         if (isRotationEnabled) {
            if (Input::IsKeyPressed(HZ_KEY_Q)) {
               transform.RotationRadians.z += (rotationSpeed * deltaTime);
            } else if (Input::IsKeyPressed(HZ_KEY_E)) {
               transform.RotationRadians.z -= (rotationSpeed * deltaTime);
            }
            if (transform.RotationRadians.z > M_PI) {
               transform.RotationRadians.z -= 2.0f * M_PI;
            } else if (transform.RotationRadians.z <= -M_PI) {
               transform.RotationRadians.z += 2 * M_PI;
            }
         }
      }

      // TODO: Do Something to set camera matrix here
   }


//   void OrthographicCameraController::OnMouseScrolled(Event& event) {
//      m_zoom -= e.GetYOffset() * 0.5f;
//      m_zoom = std::max(m_zoom, 0.25f);
//      m_cameraTranslationSpeed = m_zoom;
//      m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
//      return false;
//   }


//   bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
//      m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
//      m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
//      return false;
//   }

}