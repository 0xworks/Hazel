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
      virtual void OnUpdate() override;
      virtual void OnEvent(Event& event) override;

   private:
      bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
      bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
      bool OnMouseMoved(MouseMovedEvent& e);
      bool OnMouseScrolled(MouseScrolledEvent& e);
      bool OnKeyPressed(KeyPressedEvent& e);
      bool OnKeyReleased(KeyReleasedEvent& e);
      bool OnKeyTyped(KeyTypedEvent& e);
      bool OnWindowResize(WindowResizeEvent& e);


   private:
      float m_fTime = 0.0;
   };
}