#include "hzpch.h"
#include "OpenGlIndexBuffer.h"

#include "glad/glad.h"

namespace Hazel {

   OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* indices, const size_t count)
   : m_count(count) {
      glCreateBuffers(1, &m_indexBufferId);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
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


   size_t OpenGLIndexBuffer::GetCount() const {
      return(m_count);
   }

}


