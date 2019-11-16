#pragma once

#include "Window.h"

#include <memory>
#include <string>

struct GLFWwindow;

namespace Hazel {

   class GraphicsContext;

   class WindowsWindow : public Window {
   public:
      WindowsWindow(const WindowProps& props);
      virtual ~WindowsWindow();

      void OnUpdate() override;

      uint32_t GetWidth() const override { return m_data.Width; }
      uint32_t GetHeight() const override { return m_data.Height; }

      void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
      void SetVSync(bool enabled) override;
      bool IsVSync() const override;

      virtual void* GetNativeWindow() const override;

   private:
      GLFWwindow* m_window;
      std::unique_ptr<GraphicsContext> m_context;

      struct WindowData {
         std::string Title;
         uint32_t Width, Height;
         bool VSync;

         EventCallbackFn EventCallback;
      };

      WindowData m_data;
   };

}