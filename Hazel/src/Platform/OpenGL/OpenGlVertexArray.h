#pragma once

#include "Hazel/Renderer/VertexArray.h"

#include <memory>

namespace Hazel {

   class OpenGLVertexArray : public VertexArray {
   public:
      OpenGLVertexArray();
      virtual ~OpenGLVertexArray();

      virtual void Bind() const override;
      virtual void Unbind() const override;

      virtual void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) override;
      virtual void SetVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer) override;

      virtual VertexBuffer& GetVertexBuffer() const override;
      virtual const IndexBuffer& GetIndexBuffer() const override;

   private:
      std::unique_ptr<VertexBuffer> m_vertexBuffer;
      std::unique_ptr<IndexBuffer> m_indexBuffer;
      uint32_t m_vertexArrayId;
   };

}