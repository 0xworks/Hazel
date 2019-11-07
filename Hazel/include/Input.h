#pragma once

#include "Core.h"

namespace Hazel {

   class Input {
   public:
      Input() {}
      virtual ~Input() {}
      static bool IsKeyPressed(int keycode) { return sm_pInput->IsKeyPressedImpl(keycode); }
      static bool IsMouseButtonPressed(int button) { return sm_pInput->IsMouseButtonPressedImpl(button); }
      static float GetMouseX() { return sm_pInput->GetMouseXImpl(); }
      static float GetMouseY() { return sm_pInput->GetMouseYImpl(); }
      static std::pair<float, float> GetMousePosition() { return sm_pInput->GetMousePositionImpl(); }

   protected:
      virtual bool IsKeyPressedImpl(int keycode) = 0;
      virtual bool IsMouseButtonPressedImpl(int button) = 0;
      virtual float GetMouseXImpl() = 0;
      virtual float GetMouseYImpl() = 0;
      virtual std::pair<float, float> GetMousePositionImpl() = 0;

   private:
      static std::unique_ptr<Input> sm_pInput;
   };

}