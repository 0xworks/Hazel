#include "hzpch.h"
#include "OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace Hazel {

   OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, const uint32_t count)
   : m_count(count) {
      glCreateBuffers(1, &m_vertexBufferId);
      glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
   }


   OpenGLVertexBuffer::~OpenGLVertexBuffer() {
      glDeleteBuffers(1, &m_vertexBufferId);
   }


   const BufferLayout& OpenGLVertexBuffer::GetLayout() const {
      return(m_layout);
   }


   void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
      m_layout = layout;
   }


   void Hazel::OpenGLVertexBuffer::Bind() const {
      glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
   }


   void Hazel::OpenGLVertexBuffer::Unbind() const {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }


   uint32_t OpenGLVertexBuffer::GetCount() const {
      return(m_count);
   }
}
