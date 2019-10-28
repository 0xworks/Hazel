#pragma once

#include "Core.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

namespace Hazel {

   class HAZEL_API Application {
   public:
      Application();
      virtual ~Application();

      void Run();

      void OnEvent(Event& e);

   private:

      bool OnWindowClose(WindowCloseEvent& event);

      std::unique_ptr<Window> m_pWindow;
      bool m_bRunning = true;
   };

}


// Must be defined in client
extern Hazel::Application* CreateApplication();
