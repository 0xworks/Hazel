#pragma once

#include "Renderer/VertexBuffer.h"

namespace Hazel {

   class OpenGLVertexBuffer : public VertexBuffer {
   public:
      OpenGLVertexBuffer(const float* vertices, const uint32_t size);
      virtual ~OpenGLVertexBuffer();

      const BufferLayout& GetLayout() const override;
      virtual void SetLayout(const BufferLayout& layout) override;
      virtual void Bind() const override;
      virtual void Unbind() const override;
      virtual uint32_t GetCount() const override;

   private:
      BufferLayout m_layout;
      uint32_t m_vertexBufferId;
      uint32_t m_count;
   };
}