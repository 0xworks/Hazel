#pragma once

#include <memory>

namespace Hazel {

   class Input {
   public:
      virtual ~Input() = default;
      static bool IsKeyPressed(int keycode) { return sm_input->IsKeyPressedImpl(keycode); }
      static bool IsMouseButtonPressed(int button) { return sm_input->IsMouseButtonPressedImpl(button); }
      static float GetMouseX() { return sm_input->GetMouseXImpl(); }
      static float GetMouseY() { return sm_input->GetMouseYImpl(); }
      static std::pair<float, float> GetMousePosition() { return sm_input->GetMousePositionImpl(); }

   protected:
      virtual bool IsKeyPressedImpl(int keycode) = 0;
      virtual bool IsMouseButtonPressedImpl(int button) = 0;
      virtual float GetMouseXImpl() = 0;
      virtual float GetMouseYImpl() = 0;
      virtual std::pair<float, float> GetMousePositionImpl() = 0;

   private:
      static std::unique_ptr<Input> sm_input;
   };

}