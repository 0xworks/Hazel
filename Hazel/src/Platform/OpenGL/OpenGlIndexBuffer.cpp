#include "hzpch.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Hazel {

   OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, const uint32_t count)
   : m_count(count) {
      glCreateBuffers(1, &m_indexBufferId);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
   }


   OpenGLIndexBuffer::~OpenGLIndexBuffer() {
      glDeleteBuffers(1, &m_indexBufferId);
   }


   void OpenGLIndexBuffer::Bind() const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
   }


   void OpenGLIndexBuffer::Unbind() const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }


   uint32_t OpenGLIndexBuffer::GetCount() const {
      return m_count;
   }

}


