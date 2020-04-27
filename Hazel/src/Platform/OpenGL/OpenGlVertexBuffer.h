#pragma once

#include "Hazel/Renderer/VertexBuffer.h"

namespace Hazel {

   class OpenGLVertexBuffer : public VertexBuffer {
   public:
      OpenGLVertexBuffer(const uint32_t size);
      OpenGLVertexBuffer(const float* vertices, const uint32_t size);
      virtual ~OpenGLVertexBuffer();

      const BufferLayout& GetLayout() const override;
      virtual void SetLayout(const BufferLayout& layout) override;
      virtual void SetData(const void* data, const uint32_t size) override;
      virtual void Bind() const override;
      virtual void Unbind() const override;

   private:
      BufferLayout m_layout;
      uint32_t m_vertexBufferId;
   };
}