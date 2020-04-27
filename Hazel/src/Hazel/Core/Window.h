#pragma once

#include <memory>

namespace Hazel {

   struct WindowProps {
      std::string Title;
      uint32_t Width;
      uint32_t Height;

      WindowProps(const std::string& title = "Hazel Engine", uint32_t width = 1280, uint32_t height = 720);
   };

   // Interface representing a desktop system based Window
   class Window {
   public:
      virtual ~Window() = default;

      virtual void OnUpdate() = 0;

      virtual uint32_t GetWidth() const = 0;
      virtual uint32_t GetHeight() const = 0;

      // Window attributes
      virtual void SetVSync(bool enabled) = 0;
      virtual bool IsVSync() const = 0;

      // JRW: man this is ugly
      virtual void* GetNativeWindow() const = 0;

      static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
   };

}