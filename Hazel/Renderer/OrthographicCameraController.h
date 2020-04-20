#pragma once

#include "../Core/Timestep.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Renderer/OrthographicCamera.h"

#include "glm/glm.hpp"

namespace Hazel {

   class OrthographicCameraController {
   public:
      OrthographicCameraController(float aspectRatio, bool enableRotation = false);

      void OnUpdate(Timestep deltaTime);

      void OnEvent(Event& e);

      const OrthographicCamera& GetCamera() const;

   private:
      bool OnMouseScrolled(MouseScrolledEvent& e);

      bool OnWindowResized(WindowResizeEvent& e);

   private:
      float m_aspectRatio;
      float m_zoom;
      OrthographicCamera m_camera;
      glm::vec3 m_cameraPosition;
      float m_cameraRotation;
      float m_cameraTranslationSpeed;
      float m_cameraRotationSpeed;
      bool m_isRotationEnabled;

   };
}
