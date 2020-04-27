#include "hzpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Hazel/Events/Events.h"
#include "Hazel/Events/WindowEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>

namespace Hazel {

   static bool s_GLFWInitialized = false;


   static void GLFWErrorCallback(int error, const char* description) {
      HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
   }


   std::unique_ptr<Window> Window::Create(const WindowProps& props) {
      return std::make_unique<WindowsWindow>(props);
   }


   WindowsWindow::WindowsWindow(const WindowProps& props) {
      m_data.Title = props.Title;
      m_data.Width = props.Width;
      m_data.Height = props.Height;

      HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

      if(!s_GLFWInitialized) {
         // TODO: glfwTerminate on system shutdown
         int success = glfwInit();
         HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
         glfwSetErrorCallback(GLFWErrorCallback);
         s_GLFWInitialized = true;
      }

      m_window = glfwCreateWindow((int)props.Width, (int)props.Height, m_data.Title.c_str(), nullptr, nullptr);
      m_context = std::make_unique<OpenGLContext>(m_window);

      glfwSetWindowUserPointer(m_window, &m_data);
      SetVSync(true);

      glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         data->Width = width;
         data->Height = height;
         Events::SendEvent(WindowResizeEvent(width, height));
      });

      glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         Events::SendEvent(WindowCloseEvent());
      });

      glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

         switch(action) {
            case GLFW_PRESS: {
               Events::SendEvent(KeyPressedEvent(key, 0));
               break;
            }
            case GLFW_RELEASE: {
               Events::SendEvent(KeyReleasedEvent(key));
               break;
            }
            case GLFW_REPEAT: {
               Events::SendEvent(KeyPressedEvent(key, 1));
               break;
            }
         }
      });

      glfwSetCharCallback(m_window, [](GLFWwindow* window, uint32_t keycode) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         Events::SendEvent(KeyTypedEvent(keycode));
      });

      glfwSetMouseButtonCallback(m_window, [] (GLFWwindow* window, int button, int action, int mods) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

         switch (action) {
            case GLFW_PRESS: {
               Events::SendEvent(MouseButtonPressedEvent(button));
               break;
            }
            case GLFW_RELEASE: {
               Events::SendEvent(MouseButtonReleasedEvent(button));
               break;
            }
         }
      });

      glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         Events::SendEvent(MouseScrolledEvent(xoffset, yoffset));
      });

      glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         Events::SendEvent(MouseMovedEvent(xpos, ypos));
      });

   }


   WindowsWindow::~WindowsWindow() {
      glfwDestroyWindow(m_window);
   }


   void WindowsWindow::OnUpdate() {
      glfwPollEvents();
      m_context->SwapBuffers();
   }


   void WindowsWindow::SetVSync(bool enabled) {
      if(enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(0);

      m_data.VSync = enabled;
   }


   bool WindowsWindow::IsVSync() const {
      return m_data.VSync;
   }

   void* WindowsWindow::GetNativeWindow() const {
      return m_window;
   }

}
