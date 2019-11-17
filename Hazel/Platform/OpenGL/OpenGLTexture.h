#pragma once

#include "Renderer/Texture.h"

namespace Hazel {

   class OpenGLTexture2D : public Texture2D {
   public:
      OpenGLTexture2D(const std::string& path);
      virtual ~OpenGLTexture2D();

      virtual uint32_t GetWidth() const override;
      virtual uint32_t GetHeight() const override;

      virtual void Bind(uint32_t slot) const override;
      virtual void Unbind() const override;

   private:
      uint32_t m_textureId;
      mutable uint32_t m_slot;
      uint32_t m_width;
      uint32_t m_height;
      std::string m_path;
   };

}