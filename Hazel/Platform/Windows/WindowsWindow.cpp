#include "hzpch.h"
#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "GLFW/glfw3.h"

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
         WindowResizeEvent event(width, height);
         data->EventCallback(event);
      });

      glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         WindowCloseEvent event;
         data->EventCallback(event);
      });

      glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

         switch(action) {
            case GLFW_PRESS: {
               KeyPressedEvent event(key, 0);
               data->EventCallback(event);
               break;
            }
            case GLFW_RELEASE: {
               KeyReleasedEvent event(key);
               data->EventCallback(event);
               break;
            }
            case GLFW_REPEAT: {
               KeyPressedEvent event(key, 1);
               data->EventCallback(event);
               break;
            }
         }
      });

      glfwSetCharCallback(m_window, [](GLFWwindow* window, uint32_t keycode) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         KeyTypedEvent event(keycode);
         data->EventCallback(event);
      });

      glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

         switch(action) {
            case GLFW_PRESS: {
               MouseButtonPressedEvent event(button);
               data->EventCallback(event);
               break;
            }
            case GLFW_RELEASE: {
               MouseButtonReleasedEvent event(button);
               data->EventCallback(event);
               break;
            }
         }
      });

      glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         MouseScrolledEvent event((float)xoffset, (float)yoffset);
         data->EventCallback(event);
      });

      glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
         WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
         MouseMovedEvent event((float)xpos, (float)ypos);
         data->EventCallback(event);
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
