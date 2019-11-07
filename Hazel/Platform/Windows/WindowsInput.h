#pragma once

#include "Input.h"

namespace Hazel {

   class WindowsInput : public Input {

   public:
      WindowsInput() { /*one problem with the static pointer Input::sm_pInput is that you have no control over the order of construction.  e.g. try HZ_CORE_TRACE(...) in here and see what happens*/ }
      ~WindowsInput() {}

   protected:
      virtual bool IsKeyPressedImpl(int keycode) override;
      virtual bool IsMouseButtonPressedImpl(int button) override;
      virtual float GetMouseXImpl() override;
      virtual float GetMouseYImpl() override;
      virtual std::pair<float, float> GetMousePositionImpl() override;
   };
}