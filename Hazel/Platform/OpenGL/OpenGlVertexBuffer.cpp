#include "hzpch.h"
#include "OpenGlVertexBuffer.h"
#include "glad/glad.h"

namespace Hazel {

   OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const size_t count)
   : m_count(count) {
      glCreateBuffers(1, &m_vertexBufferId);
      glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
   }


   OpenGLVertexBuffer::~OpenGLVertexBuffer() {
      glDeleteBuffers(1, &m_vertexBufferId);
   }


   void Hazel::OpenGLVertexBuffer::Bind() const {
      glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
   }


   void Hazel::OpenGLVertexBuffer::Unbind() const {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }


   size_t OpenGLVertexBuffer::GetCount() const {
      return(m_count);
   }
}
