#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Hazel {

   OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height)
   : m_width(width)
   , m_height(height)
   , m_internalFormat(GL_RGBA8)
   , m_dataFormat(GL_RGBA)
   {
      glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
      glTextureStorage2D(m_textureId, 1, m_internalFormat, (GLsizei)m_width, (GLsizei)m_height);
      glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // TODO: need some way to abstract these parameters
      glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
   }


   OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
   : m_path(path)
   , m_width(0)
   , m_height(0)
   , m_internalFormat(0)
   , m_dataFormat(0)
   {
      int width = 0;
      int height = 0;
      int channels = 0;
      stbi_set_flip_vertically_on_load(1);
      stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
      HZ_CORE_ASSERT(data, "Failed to load image {0}", path);
      m_width = width;
      m_height = height;

      switch (channels) {
         case 3:
            m_internalFormat = GL_RGB8;
            m_dataFormat = GL_RGB;
            break;
         case 4:
            m_internalFormat = GL_RGBA8;
            m_dataFormat = GL_RGBA;
            break;
      }
      HZ_CORE_ASSERT(m_internalFormat != 0, "Texture asset contains {0} channels.  Hazel only supports 3 or 4 channels.", channels);

      glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
      glTextureStorage2D(m_textureId, 1, m_internalFormat, (GLsizei)m_width, (GLsizei)m_height);
      glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // TODO: need some way to abstract these parameters
      glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTextureSubImage2D(m_textureId, 0, 0, 0, (GLsizei)m_width, (GLsizei)m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
      glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(m_textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);

      stbi_image_free(data);
   }


   OpenGLTexture2D::~OpenGLTexture2D() {
      glDeleteTextures(1, &m_textureId);
   }


   uint32_t OpenGLTexture2D::GetId() const {
      return m_textureId;
   }


   uint32_t OpenGLTexture2D::GetWidth() const {
      return m_width;
   }


   uint32_t OpenGLTexture2D::GetHeight() const {
      return m_height;
   }
   

   void OpenGLTexture2D::SetData(const void* data, const uint32_t size) {
#ifdef HZ_ENABLE_ASSERTS
      uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
      HZ_CORE_ASSERT(size == m_width * m_height * bpp, "Texture::SetData() size parameter must equal texture width * height * bpp");
#endif
      glTextureSubImage2D(m_textureId, 0, 0, 0, m_width, m_width, m_dataFormat, GL_UNSIGNED_BYTE, data);
   }

   void Hazel::OpenGLTexture2D::Bind(uint32_t slot) const {
      glBindTextureUnit(slot, m_textureId);
      m_slot = slot;
   }


   void Hazel::OpenGLTexture2D::Unbind() const {
      glBindTextureUnit(m_slot, 0);
   }

}
