#include "hzpch.h"
#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hazel {

   static bool s_GLFWInitialized = false;


   static void GLFWErrorCallback(int error, const char* description) {
      HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
   }


   Window* Window::Create(const WindowProps& props) {
      return new WindowsWindow(props);
   }


   WindowsWindow::WindowsWindow(const WindowProps& props) {
      Init(props);
   }


   WindowsWindow::~WindowsWindow() {
      Shutdown();
   }


   void WindowsWindow::Init(const WindowProps& props) {
      m_Data.Title = props.Title;
      m_Data.Width = props.Width;
      m_Data.Height = props.Height;

      HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

      if(!s_GLFWInitialized) {
         // TODO: glfwTerminate on system shutdown
         int success = glfwInit();
         HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
         glfwSetErrorCallback(GLFWErrorCallback);
         s_GLFWInitialized = true;
      }

      m_pWindow = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
      glfwMakeContextCurrent(m_pWindow);
      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      HZ_CORE_ASSERT(status, "Could not intialize GLAD!");
      glfwSetWindowUserPointer(m_pWindow, &m_Data);
      SetVSync(true);

      glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* pWindow, int width, int height) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);
         pData->Width = width;
         pData->Height = height;
         WindowResizeEvent event(width, height);
         pData->EventCallback(event);
      });

      glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* pWindow) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);
         WindowCloseEvent event;
         pData->EventCallback(event);
      });

      glfwSetKeyCallback(m_pWindow, [](GLFWwindow* pWindow, int key, int scanCode, int action, int mods) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);

         switch(action) {
            case GLFW_PRESS: {
               KeyPressedEvent event(key, 0);
               pData->EventCallback(event);
               break;
            }
            case GLFW_RELEASE: {
               KeyReleasedEvent event(key);
               pData->EventCallback(event);
               break;
            }
            case GLFW_REPEAT: {
               KeyPressedEvent event(key, 1);
               pData->EventCallback(event);
               break;
            }
         }
      });

      glfwSetCharCallback(m_pWindow, [](GLFWwindow* pWindow, unsigned int keycode) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);
         KeyTypedEvent event((int)keycode);
         pData->EventCallback(event);
      });

      glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* pWindow, int button, int action, int mods) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);

         switch(action) {
            case GLFW_PRESS: {
               MouseButtonPressedEvent event(button);
               pData->EventCallback(event);
               break;
            }
            case GLFW_RELEASE: {
               MouseButtonReleasedEvent event(button);
               pData->EventCallback(event);
               break;
            }
         }
      });

      glfwSetScrollCallback(m_pWindow, [](GLFWwindow* pWindow, double xoffset, double yoffset) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);
         MouseScrolledEvent event((float)xoffset, (float)yoffset);
         pData->EventCallback(event);
      });

      glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* pWindow, double xpos, double ypos) {
         WindowData* pData = (WindowData*)glfwGetWindowUserPointer(pWindow);
         MouseMovedEvent event((float)xpos, (float)ypos);
         pData->EventCallback(event);
      });


   }


   void WindowsWindow::Shutdown() {
      glfwDestroyWindow(m_pWindow);
   }


   void WindowsWindow::OnUpdate() {
      glfwPollEvents();
      glfwSwapBuffers(m_pWindow);
   }


   void WindowsWindow::SetVSync(bool enabled) {
      if(enabled)
         glfwSwapInterval(1);
      else
         glfwSwapInterval(0);

      m_Data.VSync = enabled;
   }


   bool WindowsWindow::IsVSync() const {
      return m_Data.VSync;
   }

}
