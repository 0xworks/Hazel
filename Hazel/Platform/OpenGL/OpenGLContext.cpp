#include "hzpch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hazel {

   OpenGLContext::OpenGLContext(GLFWwindow* window) : m_window(window) {
      glfwMakeContextCurrent(m_window);
      int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
      HZ_CORE_ASSERT(status, "Could not intialize GLAD!");

      HZ_CORE_INFO("OpenGL Info:");
      HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
      HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
      HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
#ifdef HZ_ENABLE_ASSERTS
      int versionMajor;
      int versionMinor;
      glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
      glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
      HZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif
   }


   void OpenGLContext::SwapBuffers() {
      glfwSwapBuffers(m_window);
   }

}
