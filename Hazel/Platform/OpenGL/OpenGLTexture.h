#pragma once

#include "Renderer/Texture.h"

#include "glad/glad.h"

namespace Hazel {

   class OpenGLTexture2D : public Texture2D {
   public:
      OpenGLTexture2D(const uint32_t width, const uint32_t height);
      OpenGLTexture2D(const std::string& path);
      virtual ~OpenGLTexture2D();

      virtual uint32_t GetWidth() const override;
      virtual uint32_t GetHeight() const override;

      void SetData(const void* data, const uint32_t size) override;

      virtual void Bind(uint32_t slot) const override;
      virtual void Unbind() const override;

   private:
      uint32_t m_textureId = 0;
      mutable uint32_t m_slot = 0;
      uint32_t m_width;
      uint32_t m_height;
      GLenum m_internalFormat;
      GLenum m_dataFormat;
      std::string m_path;
   };

}