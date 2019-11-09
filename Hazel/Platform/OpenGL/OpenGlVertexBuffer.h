#pragma once

#include "Renderer/VertexBuffer.h"

namespace Hazel {

   class OpenGLVertexBuffer : public VertexBuffer {
   public:
      OpenGLVertexBuffer(const float* vertices, const size_t size);
      virtual ~OpenGLVertexBuffer();

      virtual void Bind() const override;
      virtual void Unbind() const override;
      virtual size_t GetCount() const override;

   private:
      unsigned int m_vertexBufferId;
      size_t m_count;
   };
}