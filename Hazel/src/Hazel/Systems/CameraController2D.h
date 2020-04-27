#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/ECS/System.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

   class CameraController2D: public ECS::System {
   public:

      void Init(float translationSpeed, float rotationSpeed, bool isRotationEnabled);

      void Update(Timestep deltaTime);

   private:
      void OnMouseScrolled(Event& event);
      void OnWindowResized(Event& event);

      void RecalculateViewMatrix(ECS::Entity camera);

   private:
      // TODO: better place for these.  Data doesnt belong in a System (?)
      float m_translationSpeed = 20.0f;
      float m_rotationSpeed = 10.0f;
      bool m_isRotationEnabled = true;

   };

}
