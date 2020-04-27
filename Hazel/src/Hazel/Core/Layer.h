#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

   class Layer {
   public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      virtual void OnAttach() {};
      virtual void OnDetach() {};
      virtual void OnUpdate(Timestep deltaTime) {};
      virtual void OnImGuiRender() {};

      const std::string& GetName() const;

   protected:
      std::string m_debugName;
   };

}