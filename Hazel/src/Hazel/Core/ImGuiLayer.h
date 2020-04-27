#pragma once

#include "Hazel/Core/Layer.h"

namespace Hazel {

   class ImGuiLayer : public Layer {
   public:
      ImGuiLayer();
      virtual ~ImGuiLayer();

      virtual void OnAttach() override;
      virtual void OnDetach() override;
      virtual void OnImGuiRender() override;

      static void Begin();
      static void End();

   };
}