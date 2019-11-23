#include "hzpch.h"
#include "WindowsInput.h"

#include "Core/Application.h"

#include "GLFW/glfw3.h"

namespace Hazel {

   std::unique_ptr<Input> Input::sm_input = std::make_unique<WindowsInput>();


   bool WindowsInput::IsKeyPressedImpl(int keycode) {
      GLFWwindow* pwnd = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
      return(glfwGetKey(pwnd, keycode) == GLFW_PRESS);
   }


   bool WindowsInput::IsMouseButtonPressedImpl(int button) {
      GLFWwindow* pwnd = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
      return(glfwGetMouseButton(pwnd, button) == GLFW_PRESS);
   }


   std::pair<float, float> WindowsInput::GetMousePositionImpl() {
      GLFWwindow* pwnd = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
      double x;
      double y;
      glfwGetCursorPos(pwnd, &x, &y);
      return {(float)x, (float)y};
   }


   float WindowsInput::GetMouseXImpl() {
      auto [x, y] = GetMousePositionImpl();
      return x;
   }


   float WindowsInput::GetMouseYImpl() {
      auto [x, y] = GetMousePositionImpl();
      return y;

   }

}
