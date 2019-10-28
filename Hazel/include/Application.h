#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel {

   class HAZEL_API Application {
   public:
      Application();
      virtual ~Application();

      void Run();

   private:
      std::unique_ptr<Window> m_pWindow;
      bool m_bRunning = true;
   };

}


// Must be defined in client
extern Hazel::Application* CreateApplication();
