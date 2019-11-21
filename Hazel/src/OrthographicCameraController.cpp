#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"

namespace Hazel {


   OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation)
      : m_aspectRatio(aspectRatio)
      , m_zoom(1.0f)
      , m_camera(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom)
      , m_cameraPosition(0.0f, 0.0f, 0.0f)
      , m_cameraRotation(0.0f)
      , m_cameraTranslationSpeed(m_zoom)
      , m_cameraRotationSpeed(180.0f)
      , m_isRotationEnabled(enableRotation)
   {}


   void OrthographicCameraController::OnUpdate(Timestep deltaTime) {
      if (Input::IsKeyPressed(HZ_KEY_A)) {
         m_cameraPosition.x -= (m_cameraTranslationSpeed * deltaTime);
      } else if (Input::IsKeyPressed(HZ_KEY_D)) {
         m_cameraPosition.x += (m_cameraTranslationSpeed * deltaTime);
      }

      if (Input::IsKeyPressed(HZ_KEY_S)) {
         m_cameraPosition.y -= (m_cameraTranslationSpeed * deltaTime);
      } else if (Input::IsKeyPressed(HZ_KEY_W)) {
         m_cameraPosition.y += (m_cameraTranslationSpeed * deltaTime);
      }
      m_camera.SetPosition(m_cameraPosition);

      if (m_isRotationEnabled) {
         if (Input::IsKeyPressed(HZ_KEY_Q)) {
            m_cameraRotation += (m_cameraRotationSpeed * deltaTime);
         } else if (Input::IsKeyPressed(HZ_KEY_E)) {
            m_cameraRotation -= (m_cameraRotationSpeed * deltaTime);
         }
         m_camera.SetRotation(m_cameraRotation);
      }

   }


   void OrthographicCameraController::OnEvent(Event& e) {
      EventDispatcher dispatcher(e);
      dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
      dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
   }


   const Hazel::OrthographicCamera& OrthographicCameraController::GetCamera() const {
      return m_camera;
   }

   bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
      m_zoom -= e.GetYOffset() * 0.5f;
      m_zoom = std::max(m_zoom, 0.25f);
      m_cameraTranslationSpeed = m_zoom;
      m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
      return false;
   }


   bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
      m_aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
      m_camera.SetProjection(-m_aspectRatio * m_zoom, m_zoom, m_aspectRatio * m_zoom, -m_zoom);
      return false;
   }

}