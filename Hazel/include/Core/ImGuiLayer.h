#pragma once

#include "Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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