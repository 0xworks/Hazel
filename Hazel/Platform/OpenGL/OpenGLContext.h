#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {

   class OpenGLContext : public GraphicsContext {
   public:
      OpenGLContext(GLFWwindow* window);
      virtual void SwapBuffers() override;

   private:
      GLFWwindow* m_pWindow;
   };

}
