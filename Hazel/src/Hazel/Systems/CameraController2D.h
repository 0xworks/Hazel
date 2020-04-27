#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/ECS/System.h"
#include "Hazel/Events/Event.h"

namespace Hazel {


   class CameraController2D: public System {
   public:

      void Init();

      void Update(Timestep deltaTime);

   private:

      void OnMouseScrolled(Event& event);
      void OnWindowResized(Event& event);
   };

}
