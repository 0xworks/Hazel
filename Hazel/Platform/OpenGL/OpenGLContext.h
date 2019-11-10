#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {

   class OpenGLContext : public GraphicsContext {
   public:
      OpenGLContext(GLFWwindow* window);  // note: ownership is not transferred, and destructor for OpenGLContext does not destroy the window.
      virtual void SwapBuffers() override;

   private:
      GLFWwindow* m_window;  // OpenGLContext does not own the window!
   };

}
