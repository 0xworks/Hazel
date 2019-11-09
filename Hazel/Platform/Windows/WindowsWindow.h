#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Hazel {

   class GraphicsContext;

   class WindowsWindow : public Window {
   public:
      WindowsWindow(const WindowProps& props);
      virtual ~WindowsWindow();

      void OnUpdate() override;

      unsigned int GetWidth() const override { return m_Data.Width; }
      unsigned int GetHeight() const override { return m_Data.Height; }

      void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
      void SetVSync(bool enabled) override;
      bool IsVSync() const override;

      virtual void* GetNativeWindow() const override;

   private:
      virtual void Init(const WindowProps& props);
      virtual void Shutdown();

   private:
      GLFWwindow* m_pWindow;
      GraphicsContext* m_pContext;

      struct WindowData {
         std::string Title;
         unsigned int Width, Height;
         bool VSync;

         EventCallbackFn EventCallback;
      };

      WindowData m_Data;
   };

}