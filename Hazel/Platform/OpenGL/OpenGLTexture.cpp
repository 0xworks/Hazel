#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Hazel {

   OpenGLTexture2D::OpenGLTexture2D(const std::string& path) 
   : m_textureId(0)
   , m_slot(0)
   , m_path(path)
   , m_width(0)
   , m_height(0)
   {
      int width = 0;
      int height = 0;
      int channels = 0;
      stbi_set_flip_vertically_on_load(1);
      stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
      HZ_CORE_ASSERT(data, "Failed to load image {0}", path);
      m_width = width;
      m_height = height;

      GLenum internalFormat = 0;
      GLenum format = 0;
      switch (channels) {
         case 3:
            internalFormat = GL_RGB8;
            format = GL_RGB;
            break;
         case 4:
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
            break;
      }
      HZ_CORE_ASSERT(internalFormat != 0, "Texture asset contains {0} channels.  Hazel only supports 3 or 4 channels.", channels);

      glCreateTextures(GL_TEXTURE_2D, 1, &m_textureId);
      glTextureStorage2D(m_textureId, 1, internalFormat, (GLsizei)m_width, (GLsizei)m_height);
      glTextureParameteri(m_textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // TODO: need some way to abstract these parameters
      glTextureParameteri(m_textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTextureSubImage2D(m_textureId, 0, 0, 0, (GLsizei)m_width, (GLsizei)m_height, format, GL_UNSIGNED_BYTE, data);

      stbi_image_free(data);
   }


   OpenGLTexture2D::~OpenGLTexture2D() {
      glDeleteTextures(1, &m_textureId);
   }


   uint32_t OpenGLTexture2D::GetWidth() const {
      return(m_width);
   }


   uint32_t OpenGLTexture2D::GetHeight() const {
      return(m_height);
   }
   

   void Hazel::OpenGLTexture2D::Bind(uint32_t slot) const {
      glBindTextureUnit(slot, m_textureId);
      m_slot = slot;
   }


   void Hazel::OpenGLTexture2D::Unbind() const {
      glBindTextureUnit(m_slot, 0);
   }

}
