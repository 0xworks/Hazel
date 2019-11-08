#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {

   class Layer {
   public:
      Layer(const std::string& name = "Layer");
      virtual ~Layer();

      virtual void OnAttach() {};
      virtual void OnDetach() {};
      virtual void OnUpdate() {};
      virtual void OnEvent(Event& event) {};
      virtual void OnImGuiRender() {};

      const std::string& GetName() const;
   protected:
      std::string m_DebugName;
   };

}