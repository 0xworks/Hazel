#include "hzpch.h"
#include "ImGuiLayer.h"
#include "Application.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

// should not be here
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

namespace Hazel {


   ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

   ImGuiLayer::~ImGuiLayer() {}


   void ImGuiLayer::OnAttach() {
      ImGui::CreateContext();
      ImGui::StyleColorsDark();

      ImGuiIO& io = ImGui::GetIO();
      io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
      io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

      // TEMPORARY HACK
      // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
      io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
      io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
      io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
      io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
      io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
      io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
      io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
      io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
      io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
      io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
      io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
      io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
      io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
      io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
      io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
      io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
      io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
      io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
      io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
      io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
      io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
      io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

      ImGui_ImplOpenGL3_Init("#version 410");
   }


   void ImGuiLayer::OnDetach() {}


   void ImGuiLayer::OnUpdate() {
      static bool bShow = true;

      ImGuiIO& io = ImGui::GetIO();
      Window& window = Application::Get().GetWindow();
      io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

      float fTime = (float)glfwGetTime();
      io.DeltaTime = (m_fTime > 0.0)? (fTime - m_fTime) : 1.0f / 60.0f;
      m_fTime = fTime;

      ImGui_ImplOpenGL3_NewFrame();
      ImGui::NewFrame();

      ImGui::ShowDemoWindow(&bShow);

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   }


   void ImGuiLayer::OnEvent(Event& event) {
      EventDispatcher dispatcher(event);
      dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
      dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
      dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
      dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
      dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
      dispatcher.Dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
      dispatcher.Dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
      dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResize));
   }


   bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseDown[e.GetMouseButton()] = true;
      return false;
   }


   bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseDown[e.GetMouseButton()] = false;
      return false;
   }


   bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MousePos = ImVec2(e.GetX(), e.GetY());
      return false;
   }


   bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.MouseWheelH += e.GetXOffset();
      io.MouseWheel += e.GetYOffset();
      return false;
   }


   bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e.GetKeyCode()] = true;

      io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
      io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
      io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
      io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

      return false;
   }


   bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.KeysDown[e.GetKeyCode()] = false;
      return false;
   }


   bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.AddInputCharacter(e.GetKeyCode());
      return false;
   }


   bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e) {
      ImGuiIO& io = ImGui::GetIO();
      io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
      io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

//      // does not belong here!
      glViewport(0, 0, e.GetWidth(), e.GetHeight());

      return false;
   }

}
