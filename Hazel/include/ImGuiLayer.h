#pragma once

#include "Layer.h"

namespace Hazel {

   class ImGuiLayer : public Layer {
   public:
      ImGuiLayer();
      virtual ~ImGuiLayer();

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnUpdate() override;
      virtual void OnEvent(Event& event) override;


   protected:
      float m_fTime = 0.0;
   };
}