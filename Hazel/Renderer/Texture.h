#pragma once

#include <memory>
#include <string>

namespace Hazel {

   class Texture {
   public:
      virtual ~Texture() = default;

      virtual uint32_t GetId() const = 0;
      virtual uint32_t GetWidth() const = 0;
      virtual uint32_t GetHeight() const = 0;

      virtual void SetData(const void* data, const uint32_t size) = 0;
      virtual void Bind(uint32_t slot) const = 0;
      virtual void Unbind() const = 0;
   };


   class Texture2D : public Texture {
   public:
      static std::unique_ptr<Texture2D> Create(const uint32_t width, const uint32_t height);
      static std::unique_ptr<Texture2D> Create(const std::string& path);
   };

}